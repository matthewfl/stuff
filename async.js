function async (fun, args) {
    if(!fun.length) return;
    args = args || [];
    var call=fun.shift();
    if(typeof call == "function") call = [ call ];
    var count=call.length;
    var ret=[];
    for(var at=0,len=call.length; at < len; at++
	call[at].apply((function (num){
	    function r (a) {
		ret[num]=a;
		if(!--count)
		    async(fun, ret);
	    }
	    return r;
	})(n++), args);
    }
}

exports.async = async;
