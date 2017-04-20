
require 'rubygems'
# gem 'minitest'
# require 'minitest/autorun'

require 'test/unit'
lib = File.expand_path('../../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'calc_moon'

R2D = 180.0 / Math::PI
D2R = Math::PI / 180.0
LAT = 41.9475360 * D2R
LON = -88.7430640 * D2R
# doc
class TestCalcMoonrb < Test::Unit::TestCase # MiniTest::Test
  def setup
    @t = CalcMoon.new
    @date = Date.today
  end
end

# doc
class TestSolarEclipseDay2017 < Test::Unit::TestCase # MiniTest::Test
  def setup
    @t = CalcMoon.new
    @date = Date.parse('2017-8-21')
  end
end

# doc
class TestcCalcMoonLunar < Test::Unit::TestCase # MiniTest::Test
  def setup
    @t = CalcMoon.new
    @jd = Date.new(2017, 4, 13).jd
    @ajd = Date.new(2017, 4, 13).ajd.to_f
  end

  def test_lunar_rise
    assert_equal(
      '2017-04-13 22:03:55 -0500',
      @t.lunar_rise(@ajd, LAT, LON).to_time.to_s
    )
  end

  def test_lunar_transit
    assert_equal(
      '2017-04-14 04:14:40 -0500',
      @t.lunar_transit(@ajd + 1, LAT, LON).to_time.to_s
    )
  end

  def test_lunar_set
    assert_equal(
      '2017-04-14 10:24:23 -0500',
      @t.lunar_set(@ajd + 1, LAT, LON).to_time.to_s
    )
  end
end

# doc
class TestCalcMoonST < Test::Unit::TestCase # MiniTest::Test
  def setup
    @t = CalcMoon.new
    @jd = Date.new(2017, 4, 13).jd
    @ajd = Date.new(2017, 4, 13).ajd.to_f
  end

  def test_mean_sidereal_time0
    assert_equal(
      1.457787065176914,
      @t.mean_sidereal_time(@jd)
    )
  end

  def test_mean_sidereal_time1
    assert_equal(
      13.424932152839999,
      @t.mean_sidereal_time(@ajd)
    )
  end

  def test_apparent_sidereal_time0
    assert_equal(
      1.457609695820898,
      @t.apparent_sidereal_time(@jd)
    )
  end

  def test_apparent_sidereal_time1
    assert_equal(
      13.424755361044818,
      @t.apparent_sidereal_time(@ajd)
    )
  end
end
