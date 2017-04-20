#!/usr/bin/env ruby

# require_relative "../lib/lunar_phase/moon"
# moon = LunarPhase::Moon.new
# moon.get_info

def julian(year, month, day)
  a = (14 - month) / 12
  y = year + 4800 - a
  m = (12 * a) - 3 + month
  day + (153 * m + 2) / 5 + (365 * y) + y / 4 - y / 100 + y / 400 - 32_045
end

def phase(year, month, day)
  p = (julian(year, month, day) - julian(2000, 1, 6)) % 29.530588853
  if p < 1.84566
    return 'New'
  elsif p < 5.53699
    return 'Waxing Crescent'
  elsif p < 9.22831
    return 'First Quarter'
  elsif p < 12.91963
    return 'Waxing Gibbous'
  elsif p < 16.61096
    return 'Full'
  elsif p < 20.30228
    return 'Waning Gibbous'
  elsif p < 23.99361
    return 'Last Quarter'
  elsif p < 27.68493
    return 'Waning Crescent'
  else
    return 'New'
  end
end

# puts phase(year, month, day)
