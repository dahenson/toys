
double kilowatt_hours (double watts, double hrs) {
    return (watts * hrs) / 1000;
}

double cost_per_day (double kwh_per_day, double price_per_kwh) {
    return kwh_per_day * price_per_kwh;
}

double cost_per_week (double cost_per_day) {
    return cost_per_day * 7;
}

double cost_per_month (double cost_per_day) {
    return cost_per_day * 30;
}

double cost_per_year (double cost_per_day) {
    return cost_per_day * 365;
}

double life_in_years (double lifetime_hours, double hours_per_day) {
    return lifetime_hours / hours_per_day / 365;
}
