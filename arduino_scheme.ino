#include <Adafruit_NeoPixel.h>
#include <math.h>

#define COLUMN_SIZE 8
#define COLUMNS 8
#define PIN 8         // Parameter 1 = number of pixels in strip
					  // Parameter 2 = pin number (most are valid)
					  // Parameter 3 = pixel type flags, add together as needed:
					  // NEO_KHZ800 800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
					  // NEO_KHZ400 400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
					  // NEO_GRB Pixels are wired for GRB bitstream (most NeoPixel products)
					  // NEO_RGB Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

typedef struct color_t {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

byte volume_arr[COLUMNS];
color_t from = {0, 255, 0};
color_t to = {255, 0, 0};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, PIN, NEO_GRB + NEO_KHZ800);
//lerp
void setup() {
	Serial.begin(9600);
    strip.begin();
    strip.setBrightness(50);
    strip.show();
 }

void loop() {
    /*strip.setPixelColor(i, strip.Color(255,0,0));*/
    /*strip.show();*/
	read_input();
}

/*void clear_matrix(){*/
	/*for(short i = 0; i < COLUMNS*COLUMN_SIZE; i++) {*/
		
/*}*/
void read_input() {
	short i;
	if(Serial.read() == 0xff){
		for(i=0; i<8; i++){
			byte value = Serial.read();
			Serial.println(value);
			if(value >= 255) {
				value=0;
			}
			volume_arr[i] = value;
		}
		draw_volume(from, to);
		delay(5);
	}
}

void draw_volume(color_t from_c, color_t to_c) {
	strip.clear();
	for(short i = 0; i < COLUMNS; i++) {
		light_column(i+1, volume_arr[i], from_c, to_c);
	}
    strip.show();
}

void light_column(unsigned short col, unsigned short volume, color_t from_c, color_t to_c) {
	int i = 0;
	unsigned short start = (col-1) * COLUMN_SIZE;
	for (i = start; i < start + volume; i++){
		short val = i - start+1;
		color_t c = lerp_color(from_c, to_c, (float)val/(float)COLUMN_SIZE);
		strip.setPixelColor(i, to_color(c));
	}
}

uint32_t to_color(color_t c){
	return strip.Color(c.r, c.g, c.b);
}

color_t lerp_color(color_t a, color_t b, float t) {
	color_t new_color = {
		a.r + (b.r - a.r) * t ,
		a.g + (b.g - a.g) * t ,
		a.b + (b.b - a.b) * t ,
	};
	return new_color;
}
