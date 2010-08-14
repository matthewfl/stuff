var 
DEFINE=1,
ARGS=2;

var global=this;
function _ () {
	var cmd=[];
	cmd.push(Array.prototype.slice.call(arguments));
	return function () {
		if(arguments.length==0)
			return _.run(cmd);
		else
			cmd.push(Array.prototype.slice.call(arguments));
	}
}

_.run = function (cmd) {
	var local={};
	with(local) {
	while(cmd.length) {
		var temp = cmd[0][0];
		switch(cmd[0].shift()) {
			case DEFINE:
				global[cmd[0].shift()]=cmd.[0].shift();
			case ARGS:
				while(cmd[0].length) {
					local[cmd[0].pop()]=cmd.pop(); // arguments are appended to the end of the list
				}
			default:
				if(typeof temp == "function")
					return new temp;	
		}
	}
	} //with
};


/*
 
_(DEFINE,"hi",_(ARGS, 'a', 'b')(ADD, 'a', 'b'));

_(hi)(5)(6)(); // == 11

*/
