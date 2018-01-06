#include <functional>   // std::function
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ABC {
  static uint64_t count;
  void operator ++   (int argNotUsed) {count++;}
  void operator ()   (void)           {count++;}
  virtual ABC* clone () = 0;
};
uint64_t ABC::count;
struct Y : public ABC { 
  Y                 ()                { count = 42;} 
  virtual Y* clone  ()                { return new Y(*this); }
};

int main()
{
  auto P = [] { static int call=0; cout << string("#") + to_string(++call) 
                                   + "=" + to_string(ABC::count) + "\n"; };
  Y ya, yb, yc, yd;
  for(size_t i = 2; i < 4; i++) 
    [&] { ya(); yb(); yc(); yd(); } ();
  P();

  Y y1, y2; ABC *abcPtr1 = y1.clone(), *abcPtr2 = y2.clone();
  for(size_t i = 2; i < 4; i++) 
    [&] { y1++; y2++; (*abcPtr1)++; (*abcPtr2)++; } ();
  P();

  // Y yA, yB, yC, yD;
  // vector< function<void()> > jobs { yA, yB, yC, yD };
  // vector< function<void()> > jobs { Y(), Y(), Y(), Y() };
  vector< function<void()> > jobs ( 4, Y() );
  jobs.push_back(y1);
  jobs.insert(jobs.end(), y2);
  jobs.insert(jobs.begin(), { ya, yb} );

  for(auto job: jobs)
    job();
  P();

  ABC::count = 42;
  for(auto jobInterator =jobs.begin(); jobInterator != jobs.end(); jobInterator++)
    [&] { (*jobInterator) (); } ();
  P();

  ABC::count = 42;
  while( not jobs.empty() ) {
    function< void() > job = move( jobs.back() );
    jobs.pop_back();
    job();
  }
  P();
}
