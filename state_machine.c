/******* State-machine-library for  PBA5 & other PIC-Hardware  ******************************
 *																							*
 * Titel: 			Board-Support-Library loop-delay for PIC16F877/877A						*
 * Compiler:		HI-TECH C Version 9.60PL4 and higher									*
 * Autor:			Remo Seiler, Ascom (Schweiz) AG, Berufsbildungscenter					*
 * Date:			18.05.2011															  	*
 * Last modified:	24.05.2011															  	*
 * Version:			6.0.4																  	*
 * History:			R.Seiler:	18.05.2011	Release 1 for PBA5								*
 *					R.Seiler:	23.05.2011	cleanup and optimizing event-type				*
 *					R.Seiler:	24.05.2011	add active_until_ms()-function					*
 *																							*
 * Info:			Library for implementig a state machine as a time-triggered system		*
 *					The used controller must have at least one onchip timer module.			*
 *																							*
 ********************************************************************************************/

#include <xc.h>
#include "state_machine.h"
#include "peripheral.h"

TEvents Events;

static unsigned char *state;

static unsigned char timeout_once_ms(unsigned int t){
	return (Events.time_ms==t);
}

static unsigned char timeout_ms(unsigned int t){
	return ((Events.time_ms%t) <= 10/*loopdelay_time_ms*/);	 // Returns every 't' ms a 1. The <= is necessary
	// if the loopdelay is e.g. 11ms and the timeout 20ms. Then at 22ms, when it checks this 
	// condition the expression returns a '1'
}
static unsigned char active_until_ms(unsigned int t){
	return (t<=Events.time_ms); // Max resolution is loopdelay_time_ms
}


TEvents get_events(void){
	Events.time_ms += 10/*loopdelay_time_ms*/; // Change Maybe!
	if(Events.f_state != *state){
		Events.time_ms = 0;
	}
	Events.f_state = *state;
	static unsigned char f_Taster = 0x00;
	Events.value = (((~TASTER&f_Taster)<<8)|(TASTER&~f_Taster));
	f_Taster = TASTER;
	return Events;	
}


void state_machine_init(void *s){
	state=(unsigned char *)s;
	Events.time_ms = 0;

	Events.timeout_once=timeout_once_ms;
	Events.timeout_ms=timeout_ms;
	Events.active_until_ms=active_until_ms;
}










// === COPIED from PBA Library ==========================================================
/*
#ifdef USE_STATEMACHINE_LIBRARY
	#define MAXTIMEOUTS	10
	
	static struct
	{
		unsigned char active[MAXTIMEOUTS];
		unsigned char event_occured[MAXTIMEOUTS];
		int ms[MAXTIMEOUTS];
		int end[MAXTIMEOUTS];
	} timeout_values = {0};
	
	TEvents Events;
	
	static unsigned char *state;
	static volatile unsigned int timeout_counter=0;
	static void timeout_isr_handler(void);
	static unsigned char timeout_handler(unsigned int t);
	static unsigned char active_until_ms_handler(unsigned int t);
	
	
	#define MAX_LOOP_DELAY_MS	10000
	static volatile int loop_delay_value = 0;
	
	
	void state_machine_init(void *s)
	{
		state=(unsigned char *)s;
		Events.timeout_ms=timeout_handler;
		Events.active_until_ms=active_until_ms_handler;
	}

	
// TEvents-Struct. Daten werden an Events gesendet?
TEvents get_events(void)
{
	static unsigned char FLAGS = 0;
	unsigned char Switchvalue;
	Switchvalue = PORTB;
	Events.value = ((~Switchvalue&FLAGS)<<8)|(Switchvalue&~FLAGS);
	FLAGS = Switchvalue;
	return Events;
}

static void timeout_isr_handler(void)
{
	unsigned char i;
	static unsigned char state_alt=0;
	if(state_alt!=*state)							//Bei Zustandswechsel alle Timeouts zur�cksetzen
		for(i=0;i<MAXTIMEOUTS;i++)
		{
			timeout_values.event_occured[i]=0;
			timeout_values.active[i]=0;
			timeout_values.ms[i]=0;
		}
	else
		for(i=0;i<MAXTIMEOUTS;i++)					//Timoutereignisse pr�fen
			if(timeout_values.active[i]==1 && timeout_counter==timeout_values.end[i])
				timeout_values.event_occured[i]=1;
	state_alt=*state;
	++timeout_counter;
}

static unsigned char timeout_handler(unsigned int t)
{
	unsigned char i;
	//Pr�fen ob Timeout schon vorhanden
	for(i=0; i<MAXTIMEOUTS && timeout_values.ms[i]!=t; i++);
	if(i==MAXTIMEOUTS)								//Timout noch nicht vorhanden
	{
		//Pr�fen ob noch Timeouts vorhanden sind
		for(i=0; i<MAXTIMEOUTS && timeout_values.active[i]>0; i++);
		if(i==MAXTIMEOUTS) return 0xFF;				//R�ckgabe: Fehler keine Timeouts mehr verf�gbar
		//neues Timeout speichern
		GIE=0;										//Interrupts ausschalten (counter absichern)
		timeout_values.active[i] = 1;
		timeout_values.event_occured[i]=0;
		timeout_values.ms[i] = t;
		timeout_values.end[i] = timeout_counter+t;
		GIE=1;										//Interrupts wieder einschalten
		return 0;									//R�ckgabe: Kein Timeoutereignis eingetreten
	}
	else											//Timeout bereits vorhanden
	{
		if(timeout_values.active[i] && timeout_values.event_occured[i])			//Timeoutereignis eingetreten
		{
			//Timeout zur�cksetzen
			timeout_values.event_occured[i]=0;
			timeout_values.active[i]=0;
			timeout_values.ms[i]=0;
			return 1;								//R�ckgabe: Timeoutereignis eingetreten
		}
	}
	return 0;										//R�ckgabe: Kein Timeoutereignis eingetreten
}

static unsigned char active_until_ms_handler(unsigned int t)
{
	unsigned char i;
	//Pr�fen ob Timeout schon vorhanden
	for(i=0; i<MAXTIMEOUTS && timeout_values.ms[i]!=t; i++);
	if(i==MAXTIMEOUTS)								//Timout noch nicht vorhanden
	{
		//Pr�fen ob noch Timeouts vorhanden sind
		for(i=0; i<MAXTIMEOUTS && timeout_values.active[i]>0; i++);
		if(i==MAXTIMEOUTS) return 0xFF;				//R�ckgabe: Fehler keine Timeouts mehr verf�gbar
		//neues Timeout speichern
		GIE=0;										//Interrupts ausschalten (counter absichern)
		timeout_values.active[i] = 1;
		timeout_values.event_occured[i]=0;
		timeout_values.ms[i] = t;
		timeout_values.end[i] = timeout_counter+t;
		GIE=1;										//Interrupts wieder einschalten
		return 1;									//R�ckgabe: Kein Timeoutereignis eingetreten
	}
	else											//Timeout bereits vorhanden
	{
		if(timeout_values.active[i]==2)			//Ontime-Timemout bereits 1x abgelaufen
			return 0;		
		if(timeout_values.active[i] && timeout_values.event_occured[i])			//Timeoutereignis eingetreten
		{
			//Timeout zur�cksetzen
			timeout_values.event_occured[i]=0;
			timeout_values.active[i]=2;
			return 0;								//R�ckgabe: Timeoutereignis eingetreten
		}
	}
	return 1;										//R�ckgabe: Kein Timeoutereignis eingetreten
}

#endif
*/