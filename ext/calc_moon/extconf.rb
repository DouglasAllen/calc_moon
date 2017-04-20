#!/usr/local/bin/ruby

require 'mkmf'
RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']
extension_name = 'calc_moon/calc_moon'
dir_config(extension_name)
create_makefile(extension_name)