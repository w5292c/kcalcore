#!/usr/bin/ruby

# This file is part of the syndication library
#
# Copyright (C) 2005 Frank Osterfeld <osterfeld@kde.org>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public License
# along with this library; see the file COPYING.LIB.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301, USA.

SUBDIRS = [ 'rss2', 'rdf', 'atom' ]

TESTLIBSYNDICATION='../../build/syndication/tests/testlibsyndication'

numTotal = 0
numErrors = 0

files = Array.new

SUBDIRS.each do |dir|
    Dir.foreach(dir) do |i|
        files.push(dir + "/" + i) if i =~ /.*\.xml\Z/
    end
end

files.each do |file|
    expectedfn = file + ".expected"
    if File.exist?(expectedfn)
        expFile = File.open(expectedfn, "r")
        expected = expFile.read
        expFile.close
        
        system("#{TESTLIBSYNDICATION} #{file} > testfeeds-output.tmp")
        actFile = File.open("testfeeds-output.tmp")
        actual = actFile.read
        actFile.close
        
        numTotal += 1
        if actual != expected
            puts "#{file} parsed incorrectly (abstraction)."
            # TODO: add diff to log
            numErrors += 1
        end
              
    end
    specificfn = file + ".expected-specific"
    if File.exist?(specificfn)
        specFile = File.open(specificfn, "r")
        specific = specFile.read
        specFile.close
        
        system("#{TESTLIBSYNDICATION} --specific-format #{file} > testfeeds-output.tmp")
        actFile = File.open("testfeeds-output.tmp")
        actual = actFile.read
        actFile.close
        
        numTotal += 1
        if actual != specific
            puts "#{file} parsed incorrectly (specific format)."
            # TODO: add diff to log
            numErrors += 1
        end
              
    end

end
# TODO print more verbose output
exit(numErrors)

