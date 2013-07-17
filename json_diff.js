function compareObject (objFrom, objTo) {
    var changed = false;
    var fix = {};
    var replaces = {};
    var remove = [];
    for(var a in objFrom) {
	if(typeof objTo[a] == 'undefined') {
	    remove.push(a);
	    changed = true;
	}
    }
    for(var a in objTo) {
	if(typeof objFrom[a] != typeof objTo[a]) {
	    // replace
	    replaces[a] = objTo[a];
	    changed = true;
	    continue;
	}
	switch(typeof objFrom[a]) {
	case 'object':
	    if(objFrom[a] instanceof Array) {
		var d = compareArray(objFrom[a], objTo[a]);
		if(d !== false) {
		    fix[a] = d;
		    changed = true;
		}
	    }else{
		var d = compareObject(objFrom[a], objTo[a]);
		if(d !== false) {
		    fix[a] = d;
		    changed = true;
		}
	    }
	    break;
	case 'boolean':
	    if(objFrom[a] != objTo[a]) {
		changed = true;
		replace[a] = objTo[a];
	    }
	case 'string':

	}
    }

    if(changed) {
	return {
	    'type': 'obj',
	    'remove': remove,
	    'replace': replace,
	    'fix': fix
	};
    }else{
	return false;
    }
}

function applyObject(objFrom, diff) {
    if(diff.type != 'obj') return false;

    // copy objFrom I guess
    for(var a in diff.remove) {
	delete objFrom[a];
    }
    for(var a in diff.replace) {
	objFrom[a] = diff.replace[a];
    }
    for(var a in diff.fix) {
	switch(diff.fix[a].type) {
	    case 'obj':
	    objFrom[a] = applyObject(objFrom[a], diff.fix[a]);
	    break;
	    case 'array':
	    // stuff
	}
    }
}
