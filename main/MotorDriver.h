#ifndef MotorDriver_h
#define MotorDriver_h

struct Motor {
  int en;
  int in1;
  int in2;
};

#define FAST 70
#define SLOW 40
#define BOOST_DELAY 50
#define TURN_DELAY 100
#define TURN180_DELAY 1000

class MotorDriver {
	private:
		void update_wheel(Motor mcur, int power);

	public:
		MotorDriver();
		void init();
		void update_drive(int power);
		void update_left(int power);
		void update_right(int power);
		void stop_all();

		void turn_right();
		void turn_left();
    void turn_180();
		void forward_fast();
		void forward_slow();
		void back_fast();
		void back_slow();
};


#endif
