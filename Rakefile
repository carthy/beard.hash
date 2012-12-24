require 'rake'
require 'rake/clean'
require 'tmpdir'

CFLAGS = "-Wall -Werror-implicit-function-declaration -std=c11 -g0 -O3 -funroll-loops -I. #{ENV['CFLAGS']}"

SOURCES = FileList['*.c'].exclude('test.c')
OBJECTS = SOURCES.ext('o')

CLEAN.include(OBJECTS)
CLOBBER.include('hash.a', 'test-it')

task :default => 'build:hash'

task :test => 'build:test' do
	sh './test-it'
end

namespace :build do
	task :hash => 'hash.a'

	task :test => 'test-it'

	file 'hash.a' => OBJECTS do
		sh "ar rcs hash.a #{OBJECTS}"
	end

	file 'test-it' => OBJECTS do
		sh "clang #{CFLAGS} #{OBJECTS} test.c -o test-it"
	end
end

rule '.o' => '.c' do |t|
	sh "clang #{CFLAGS} -o #{t.name} -c #{t.source}"
end
