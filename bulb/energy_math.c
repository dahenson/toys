
double
kilowatt_hours(double watts, double hrs)
{
    return (watts * hrs) / 1000;
}

double
cost_per_day(double kwh_per_day, double price_per_kwh)
{
    return kwh_per_day * price_per_kwh;
}

