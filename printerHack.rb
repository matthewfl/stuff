require 'socket'
#require 'ping'

def print (attr, what)
	begin
		s = TCPSocket.open(attr, 9100)
		s.puts what
		s.close
		return true
	rescue
		return false
	end
end

def input
	text = ""
	line = ""
	while nil == (line =~ /PRINT/) do
		text += "#{line}\r"
		line = gets
	end
	text
end

class Ip
	def initialize (start, last)
		@ip = start
		@last = last
		@last[3] += 1
	end
	def Next
		@ip[3] += 1
		4.times do |n|
			if @ip[4-n] == 256
				@ip[3-n] += 1
				@ip[4-n] = 0
			end
		end
	end
	def ip
		@ip.join "."
	end
	def done
		@ip != @last
	end
	def do
		while self.done do
			yield self.ip
			self.Next
		end
	end
end

def main
	text = input.gsub("\n", "\n\r")
	ip = Ip.new( [192,168,0,1], [192,168,254,254])
	ip.do do |i|
		if print(i, "") == true do
			puts "Printed to #{i}"
		end
		ip.Next
	end
	#print("10.0.1.4", Message)
end


main
