#ifndef ENERGY_MATH_H_
#define ENERGY_MATH_H_

double kilowatt_hours (double watts, double hrs);
double cost_per_day (double kwh_per_day, double price_per_kwh);
double cost_per_week (double cost_per_day);
double cost_per_month (double cost_per_day);
double cost_per_year (double cost_per_day);
double life_in_years (double lifetime_hours, double hours_per_day);

#endif /* ENERGY_MATH_H_ */
