# encoding: utf-8

require 'rubygems'
require 'bundler'
begin
  Bundler.setup(:default, :development)
rescue Bundler::BundlerError => e
  $stderr.puts e.message
  $stderr.puts 'Run `bundle install` to install missing gems'
  exit e.status_code
end
require 'bundler/gem_tasks'

require 'hoe'

require 'rake'
require 'rake/clean'
require 'rake/extensiontask'
require 'rake/testtask'
require 'rake/win32'
require 'rdoc/task'
require 'rspec/core/rake_task'
require 'yard'

require 'rbconfig'
include RbConfig

Hoe.plugin :manifest

Hoe.spec 'calc_moon' do
  developer('Douglas Allen', 'kb9agt@gmail.com')
  license('MIT')
  self.readme_file   = 'README.rdoc'
  self.history_file  = 'History.rdoc'
  self.version = '1.0.0'
  self.extra_dev_deps += [
    ['rake-compiler',      '~> 0.9.2'],
    ['rake-compiler-dock', '~> 0.5.1']
  ]
  self.spec_extras = { extensions: ['ext/calc_moon/extconf.rb'] }
  Rake::ExtensionTask.new('calc_moon', spec) do |ext|
    ext.lib_dir = File.join('lib', 'calc_moon')
  end
end

Rake::Task[:test].prerequisites << :compile
# vim: syntax=ruby

Rake::TestTask.new(:test) do |t|
  t.libs << 'test'
  t.libs << 'lib'
  t.test_files = FileList['test/test_*.rb']
end

spec = Gem::Specification.new do |s|
  s.name = 'calc_moon'
  s.platform = Gem::Platform::RUBY
  s.extensions = FileList['ext/**/extconf.rb']
end
Gem::PackageTask.new(spec) do |pkg|
end

task default: :test
