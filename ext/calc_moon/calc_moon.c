
#include <ruby.h>
#include <math.h>
#include <time.h>
#include <libnova/libnova.h>

# define DJ00 2451545.0L
# define RND12 1000000000000.0L
#ifndef PI
#define PI 3.1415926535897932384626433832795028841971L
#endif
#ifndef DBL2NUM
# define DBL2NUM(dbl) rb_float_new(dbl)
#endif
# define PI2 PI * 2.0
# define R2D 57.295779513082320876798154814105L
# define D2R 0.017453292519943295769236907684886L
# define M2PI M_PI * 2.0

/* macro for normalizing
* angles into 0-2pie range
*/
static inline double
anp(double angle){
  double w = fmod(angle, M2PI);
  if (w < 0) w += M2PI;
  return w;
}
/*
 * call-seq:
 *  initialize()
 *
 * Create CalcMoon class instance Ruby object.
 *
 */
static VALUE t_init(VALUE self){
  return self;
}
/*
 * call-seq:
 *   mean_sidereal_time(ajd)
 *
 * returns Greenwich Mean Sidereal Time in hours.
 */
static VALUE gmst(VALUE self, VALUE vajd){
  double mst = ln_get_mean_sidereal_time(NUM2DBL(vajd));
  return DBL2NUM(mst);
}
/*
 * call-seq:
 *   apparent_sidereal_time(ajd)
 *
 * returns Greenwich Apparent Sidereal Time in hours.
 */
static VALUE gast(VALUE self, VALUE vajd){
  double ast = ln_get_apparent_sidereal_time(NUM2DBL(vajd));
  return DBL2NUM(ast);
}

/*
 * call-seq:
 *   lunar_rise(ajd, lat, lon)
 *
 * returns a DateTime object for Lunar Rise.
 */
static VALUE lun_rise(VALUE self, VALUE vajd, VALUE vlat, VALUE vlon){
  double jd = floor(NUM2DBL(vajd));
  int year, month, day, hour, min, sec;
  VALUE cDateTime = rb_const_get(rb_cObject, rb_intern("DateTime"));
  struct ln_lnlat_posn observer;
  struct ln_rst_time rst;
	struct ln_zonedate rise;
  observer.lat = NUM2DBL(vlat);
	observer.lng = NUM2DBL(vlon);
  if (ln_get_lunar_rst (jd, &observer, &rst) == 1)
		printf ("Moon is circumpolar\n");
	else {
		ln_get_local_date (rst.rise, &rise);
  }
  year = INT2NUM(rise.years);
  month = INT2NUM(rise.months);
  day = INT2NUM(rise.days);
  hour = INT2NUM(rise.hours);
  min = INT2NUM(rise.minutes);
  sec = INT2NUM(round(rise.seconds));
  return rb_funcall(cDateTime, rb_intern("new"), 6,
    year, month, day, hour, min, sec);
}

/*
 * call-seq:
 *   lunar_tranist(ajd, lat, lon)
 *
 * returns a DateTime object for Lunar Transit.
 */
static VALUE lun_trans(VALUE self, VALUE vajd, VALUE vlat, VALUE vlon){
  double jd = floor(NUM2DBL(vajd));
  int year, month, day, hour, min, sec;
  VALUE cDateTime = rb_const_get(rb_cObject, rb_intern("DateTime"));
  struct ln_lnlat_posn observer;
  struct ln_rst_time rst;
	struct ln_zonedate transit;
  observer.lat = NUM2DBL(vlat);
	observer.lng = NUM2DBL(vlon);
  if (ln_get_lunar_rst (jd, &observer, &rst) == 1)
		printf ("Moon is circumpolar\n");
	else {
		ln_get_local_date (rst.transit, &transit);
  }
  year = INT2NUM(transit.years);
  month = INT2NUM(transit.months);
  day = INT2NUM(transit.days);
  hour = INT2NUM(transit.hours);
  min = INT2NUM(transit.minutes);
  sec = INT2NUM(round(transit.seconds));
  return rb_funcall(cDateTime, rb_intern("new"), 6,
    year, month, day, hour, min, sec);
}
/*
 * call-seq:
 *   lunar_set(ajd, lat, lon)
 *
 * returns a DateTime object for Lunar Set.
 */
static VALUE lun_set(VALUE self, VALUE vajd, VALUE vlat, VALUE vlon){
  double jd = floor(NUM2DBL(vajd));
  int year, month, day, hour, min, sec;
  VALUE cDateTime = rb_const_get(rb_cObject, rb_intern("DateTime"));
  struct ln_lnlat_posn observer;
  struct ln_rst_time rst;
	struct ln_zonedate set;
  observer.lat = NUM2DBL(vlat);
	observer.lng = NUM2DBL(vlon);
  if (ln_get_lunar_rst (jd, &observer, &rst) == 1)
		printf ("Moon is circumpolar\n");
	else {
		ln_get_local_date (rst.set, &set);
  }
  year = INT2NUM(set.years);
  month = INT2NUM(set.months);
  day = INT2NUM(set.days);
  hour = INT2NUM(set.hours);
  min = INT2NUM(set.minutes);
  sec = INT2NUM(round(set.seconds));
  return rb_funcall(cDateTime, rb_intern("new"), 6,
    year, month, day, hour, min, sec);
}



void Init_calc_moon(void){
  VALUE cCalcMoon = rb_define_class("CalcMoon", rb_cObject);
  rb_require("date");
  rb_define_method(cCalcMoon, "initialize", t_init, 0);
  rb_define_method(cCalcMoon, "mean_sidereal_time", gmst, 1);
  rb_define_method(cCalcMoon, "apparent_sidereal_time", gast, 1);
  rb_define_method(cCalcMoon, "lunar_rise", lun_rise, 3);
  rb_define_method(cCalcMoon, "lunar_transit", lun_trans, 3);
  rb_define_method(cCalcMoon, "lunar_set", lun_set, 3);
}