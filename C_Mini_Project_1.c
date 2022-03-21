#include <stdlib.h>
#include <stdio.h>
#define ON 1
#define OFF 0
#define WITH_ENGINE_TEMP_CONTROLLER 1 //set to 0 to disable

enum vehicle_state{
	engine_off,		/*state0*/
	engine_on,  	/*state1*/
	quit_system		/*state2*/
};

enum vehicle_state state=0;
char traffic_light,AC;
unsigned int engine_temp_controller, turn_off;
float room_temp=20,engine_temp=90,speed;
int operation;

void state0();
void state1();
void state2();
void trafficLight();
void roomTemp();
void engineTemp();
void display();


void trafficLight(){
	printf("Enter Traffic Light Colour (G,O,R): \n");
	fflush(stdin);
	scanf("%c",&traffic_light);
	switch(traffic_light){
	case 'g':
	case 'G':
		speed=100;
		break;
	case 'o':
	case 'O':
		speed=30;
		break;
	case 'r':
	case 'R':
		speed=0;
		break;
	}
}

void roomTemp(){
	printf("Enter Room Temperature: \n");
	scanf("%f",&room_temp);
	if(room_temp<10){
		AC=ON;
		room_temp=20;
	}
	else if (room_temp>30){
		AC=ON;
		room_temp = 20;
	}
	else{
		AC=OFF;
	}
}

void engineTemp(){
	printf("Enter Engine Temp: \n");
	scanf("%f",&engine_temp);
#if (WITH_ENGINE_TEMP_CONTROLLER==1)

	if(engine_temp<100){
		engine_temp_controller=ON;
		engine_temp=125;
	}
	if(engine_temp>150){
		engine_temp_controller=ON;
		engine_temp=125;
	}
	else{
		engine_temp_controller=OFF;
	}
	if(speed==30){
		if(AC==OFF){
			AC=ON;
			room_temp=room_temp*(5.0/4.0)+1;
		}
		if(engine_temp_controller==OFF){
			engine_temp_controller=ON;
			engine_temp=engine_temp*(5.0/4.0)+1;
		}
	}
#else
	printf("WITHOUT ENGINE TEMP CONTROLLER.\n\n");
#endif
}

void state0(){
	if(state==1){
		printf("Engine has stopped successfully.\n");
	}
	else{
		printf("Engine is already OFF.\n");
	}
	printf("Choose what you want to do next.\n");
	printf("1) 0 for turning off the engine.\n2) 1 for turning on the engine.\n3) 2 to quit the system.\n");
	scanf("%d",&state);
	if(state==0){
		state0();
	}
	else if(state==1){
		state1();
		return;
	}
	else if(state==2){
		state2();
		return;
	}
	else {
		printf("Invalid Choice.\n");
	}
}

void state1(){
	int i;
	for(i = 0; i < 3; ++i){
		printf("Sensors Set Menu\n");
		printf("Choose an Operation: (1,2,3,4)\n");
		printf("1) Turn off the engine. \t");
		printf("2) Set the traffic light color.\n");
		printf("3) Set the room temperature.\t");
		printf("4) Set the engine temperature.\n");
		scanf("%d",&operation);
		if(operation==1){
			state0();
			return;
		}
		switch(operation){
		case 2:
			trafficLight();
			display();
			break;
		case 3:
			roomTemp();
			display();
			break;
		case 4:
			engineTemp();
			display();
			break;
		}
	}
	state1();
}

void state2(){
	return;
}

void display(){
	if(state==1 || state==0){
		printf("=====================================");
		if(state==1){
			printf("\nEngine State: ON. \n");
		}
		else{
			printf("\nEngine State: OFF. \n");
		}
		if(AC==ON){
			printf("AC: ON. \n");
		}
		else{
			printf("AC: OFF. \n");
		}
		printf("Vehicle Speed: %fkm/hr.\n",speed);
		printf("Room Temperature: %f°C\n",room_temp);
		if(engine_temp_controller==ON){
			printf("Engine Temperature Controller State: ON.\n");
		}
		else {
			printf("Engine Temperature Controller State: OFF.\n");
		}
		printf("Engine Temperature: %f.\n",engine_temp);
		printf("=====================================\n");
	}
}


void main(){
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("Please choose the desired state.\n");
	printf("1) 0 for turning off the engine.\n2) 1 for turning on the engine.\n3) 2 to quit the system.\n");
	scanf("%d",&state);

	if(state==0){
		state0();
	}
	else if (state==1){
		state1();
	}
	else if(state==2){
		printf("Vehicle System has quitted successfully.\n");
		return;
	}
}

