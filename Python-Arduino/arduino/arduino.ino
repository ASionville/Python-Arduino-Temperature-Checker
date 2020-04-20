const int cpu_green_pin_1 = 5;
const int cpu_green_pin_2 = 6;
const int cpu_green_pin_3 = 7;
const int cpu_yellow_pin_1 = 8;
const int cpu_yellow_pin_2 = 9;
const int cpu_yellow_pin_3 = 10;
const int cpu_red_pin_1 = 2;
const int cpu_red_pin_2 = 3;
const int cpu_red_pin_3 = 4;

const int gpu_green_pin_1 = 12;
const int gpu_green_pin_2 = A0;
const int gpu_green_pin_3 = A1;
const int gpu_yellow_pin_1 = A2;
const int gpu_yellow_pin_2 = A3;
const int gpu_yellow_pin_3 = A4;
const int gpu_red_pin_1 = A5;
const int gpu_red_pin_2 = A6;
const int gpu_red_pin_3 = A7;

const int all_pins[] = {cpu_green_pin_1, cpu_green_pin_2, cpu_green_pin_3, cpu_yellow_pin_1, cpu_yellow_pin_2, cpu_yellow_pin_3, cpu_red_pin_1, cpu_red_pin_2, cpu_red_pin_3, gpu_green_pin_1, gpu_green_pin_2, gpu_green_pin_3, gpu_yellow_pin_1, gpu_yellow_pin_2, gpu_yellow_pin_3, gpu_red_pin_1, gpu_red_pin_2, gpu_red_pin_3};

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

	for (int i=0; i<18; i++){
		digitalWrite(all_pins[i], HIGH);
	}

	String data = Serial.readString();
	int length = data.length();
	int g_pos = data.indexOf("G");

	String cpu_data = data.substring(0, g_pos);
	String gpu_data = data.substring(g_pos);

	int cpu_temperature = cpu_data.toInt();
	int gpu_temperature = gpu_data.toInt();

	if (cpu_temperature <= 92){
		digitalWrite(cpu_red_pin_3, LOW);
	}
	if (cpu_temperature <= 86){
		digitalWrite(cpu_red_pin_2, LOW);
	}
	if (cpu_temperature <= 80){
		digitalWrite(cpu_red_pin_1, LOW);
	}
	

	if (cpu_temperature <= 70){
		digitalWrite(cpu_yellow_pin_3, LOW);
	}
	if (cpu_temperature <= 60){
		digitalWrite(cpu_yellow_pin_2, LOW);
	}
	if (cpu_temperature <= 50){
		digitalWrite(cpu_yellow_pin_1, LOW);
	}
	

	if (cpu_temperature <= 40){
		digitalWrite(cpu_green_pin_3, LOW);
	}
	if (cpu_temperature <= 30){
		digitalWrite(cpu_green_pin_2, LOW);
	}
	




	if (gpu_temperature <= 92){
		digitalWrite(gpu_red_pin_3, LOW);
	}
	if (gpu_temperature <= 86){
		digitalWrite(gpu_red_pin_2, LOW);
	}
	if (gpu_temperature <= 80){
		digitalWrite(gpu_red_pin_1, LOW);
	}
	

	if (gpu_temperature <= 70){
		digitalWrite(gpu_yellow_pin_3, LOW);
	}
	if (gpu_temperature <= 60){
		digitalWrite(gpu_yellow_pin_2, LOW);
	}
	if (gpu_temperature <= 50){
		digitalWrite(gpu_yellow_pin_1, LOW);
	}
	

	if (gpu_temperature <= 40){
		digitalWrite(gpu_green_pin_3, LOW);
	}
	if (gpu_temperature <= 30){
		digitalWrite(gpu_green_pin_2, LOW);
	}
}
