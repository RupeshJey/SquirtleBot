#ifndef MotorDriver_h
#define MotorDriver_h

struct Motor {
  int en;
  int in1;
  int in2;
};

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
		void turn_right(int power);
		void turn_left(int power);

};


#endif