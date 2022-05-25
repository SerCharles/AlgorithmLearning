#ifndef CP_INTEGER_H
#define CP_INTEGER_H

//extern int integer_input();
class cp_integer
{
  private: 
	  int real_num;
	  int num;
	  void i_input();
	  void i_input(int max);
	  void i_input(int min, char c);
	  void i_input(int min, int max);
  public:
	  cp_integer():num(0),real_num(0){ }
      ~cp_integer(){}
  public:
	  void set(int i);
	  int get();
	  void input();
	  void input(int max);
	  void input(int min, char c);
	  void input(int min, int max);
	  void output();
};


#endif