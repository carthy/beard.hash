require 'rake'
require 'rake/clean'
require 'tmpdir'

CFLAGS = "-Wall -Werror-implicit-function-declaration -std=c11 -Iinclude #{ENV['CFLAGS']}"

SOURCES = FileList['sources/*.c']
OBJECTS = SOURCES.ext('o')

CLEAN.include(OBJECTS)
CLOBBER.include('hash.a', 'hash.h')

task :default => :build

task :build, :mode do |t, args|
	mode = (args[:mode] || :debug).to_sym

	if mode == :debug
		CFLAGS << ' -O0 -g3'
	else
		CFLAGS << ' -g0 -O3 -funroll-loops -finline-functions -DNDEBUG'
	end

	Rake::Task['build:hash'].invoke
end

namespace :build do
	task :hash => ['hash.a', 'hash.h']

	file 'hash.a' => OBJECTS do
		sh "ar rcs hash.a #{OBJECTS}"
	end

	file 'hash.h' => FileList['include/*.h'] do
		header = File.read('include/common.h')

		%w[siphash crapwow murmur3].each {|name|
			header << File.read("include/#{name}.h").sub(/\A.*\*\/\n/m, '')
		}

		File.open('hash.h', 'w') {|f|
			f.puts(header)
		}
	end
end

task :test => 'test:run'

namespace :test do
	task :build => 'test/run'

	task :run => 'test:build' do
		sh 'test/run'
	end

	file 'test/run' => ['run.c', 'hash.a', 'hash.h'] do
		sh "clang #{CFLAGS} -I. -o test/run test/run.c hash.a"
	end

	file 'run.c'
end

rule '.o' => '.c' do |t|
	sh "clang #{CFLAGS} -o #{t.name} -c #{t.source}"
end

rule '.h'
