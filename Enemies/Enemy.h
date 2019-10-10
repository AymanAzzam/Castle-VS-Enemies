#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

// Enemy is the base class of each type of enemy
// Enemy is an abstract class.

class Tower;

class Enemy
{

protected:
	int ID;         //Each enemy has a unique ID (sequence number)
	color Clr;	    //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;  //Region of this enemy
	int Distance;	//Horizontal distance between enemy & the tower of its region
					//Always positive (ranges from 2 to 60)
	double Health;	//Enemy health

	int arrivaltimestamp;
	int firepower;
	int reloadperiod;

	int attackingtime;

	Tower * tow;

	int killedtime;
	int state;		//if 0->killed && if 1->inactive && if 2->active
	double damage; // the damage it cause


	int firstshoot;

	int speed;  //bonus

	MenuItem ACT;

public:


	Enemy::Enemy(); //default constr to avoid errors
	Enemy(color r_c, REGION r_region, int arrts, double ffpp, double repe, double h, int s = 1);
	virtual ~Enemy();


	color GetColor() const;
	REGION GetRegion() const;

	void DecrementDist();

	void SetDistance(int d);
	int GetDistance() const;

	// Virtual Functions: ----------------

	virtual void Move() = 0;	    //All enemies can move
	virtual void Attack(int) = 0;	//All enemies can attack (attacking is paving or shooting)

	virtual double get_priority() const;

	void set_tower(Tower * t);

	void set_ats(int);				//takes arrival time stamp
	int get_ats()const;			// return arrival time stamp

	void set_fp(double);			// set fire power
	double get_fp()const;			//get fire power

	void set_health(double);		//setting health
	double get_health() const;		// getting health

	void set_reloadtime(int);	//setting rt
	int get_reloadtime() const;	//getting reload time

	//adding function that sets the killed time
	//adding function that gets the killed time
	//but after knowing the current time is where

	void thestate(int);			//their implementation will be made after knowing the current time && in it make the (attackingtime)=(arrival time)
	int get_state() const;

	double get_damage() const;

	void set_region(REGION);

	void set_speed(double);        //set the speed of the enemy (bonus)
	double get_speed()const;

	int getfirstshootdelay() const;

	int killdelay() const;

	int lifetime() const;

	void treatment(Enemy *);

	virtual void calc_damage_effect_on_me(int currenttime) = 0;

	virtual bool isshielded() const;


	bool iskilled() const;

	void setID(int);
	int getID() const;

	virtual bool operator<(const Enemy& e) const;
	virtual bool Enemy:: operator > (const Enemy & e) const;
	bool priorityCmp(const Enemy& e) const;

	void step(int currenttime, MenuItem action);
	void treatment(double);

	int killed_time_step() const;

	virtual void Enemy::cal_remaining_time(int currenttime);
};
