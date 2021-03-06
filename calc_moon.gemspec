# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'calc_moon/version'

Gem::Specification.new do |spec|
  spec.name          = 'calc_sun'
  spec.version       = CalcMoon::VERSION
  spec.author        = 'Douglas Allen'
  spec.email         = ['kb9agt@gmail.com']
  spec.summary       = 'Calculates Sun Times ea. rise, noon, set'
  spec.description   = 'Given a Julian Day Number of day,
                        latitude decimal, and
                        longitude decimal in the calls to instance methods
                        rise(jd, lat, lon),
                        noon(jd, lat, lon), and
                        set(jd, lat, lon)
                        see source code for more details'
  spec.homepage      = 'https://github.com/DouglasAllen/calc_moon'
  spec.license       = 'MIT'
  require 'English'
  spec.files = `git ls-files -z`.split("\x0").reject do |f|
    f.match(%r{^(test|spec|features)/})
  end
  require 'rake'
  spec.extensions << 'ext/extconf.rb'
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ['lib']
  spec.platform = Gem::Platform::RUBY
end
