import ddf.minim.analysis.*;
import ddf.minim.*;
import processing.serial.*;
 
Serial port;
 
Minim minim;
AudioInput in;
FFT fft;

int buffer_size = 1024;
float sample_rate = 44100;

float freq_height;

void setup()
{
  size(200, 200);
  
  minim = new Minim(this);
  port = new Serial(this, Serial.list()[0],9600);
  in = minim.getLineIn(Minim.MONO,buffer_size,sample_rate);
 
  fft = new FFT(in.bufferSize(), in.sampleRate());
  fft.window(FFT.HAMMING);
}


void draw()
{
  fft.forward(in.mix);
  
  freq_height = fft.calcAvg((float) 0, (float) 5600);
  
  byte freq = 1;
  if(freq_height > 1) {
    freq = 10;
  } else if (freq_height < 1 && freq_height > 0.6) {
    freq = 9;
  } else if (freq_height < 0.6 && freq_height > 0.3) {
    freq = 8;
  } else if (freq_height < 0.3 && freq_height > 0.2) {
    freq = 7;
  } else if (freq_height < 0.2 && freq_height > 0.1) {
    freq = 6;
  } else if (freq_height < 0.1 && freq_height > 0.04) {
    freq = 5;
  } else if (freq_height < 0.04 && freq_height > 0.01) {
    freq = 4;
  } else if (freq_height < 0.01 && freq_height > 0.008) {
    freq = 3;
  } else if (freq_height < 0.008 && freq_height > 0.005) {
    freq = 2;
  } else if (freq_height < 0.005) {
    freq = 1;
  } 
  
  
  port.write(0xff);
  port.write(freq);
  
  delay(30);
}
 
 
void stop()
{
  // always close Minim audio classes when you finish with them
  in.close();
  minim.stop();
 
  super.stop();
}