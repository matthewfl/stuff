var 	IF=1,
	DEFINE=2,
	ADD=3,
	SUBTRACT=4;

var global=this;

function _ (_name, _a1, _a2, _a3, _a4) {
	// the main function
	try {
		switch(_name) {
			case IF:
				return _a1 ? _a2 : _a3;
			case DEFINE:
				return global[_a1]=_a2;
			case ADD:
				return _a1 + _a2;
			case SUBTRACT:
				return _a1 - _a2;
			default:
				return _;
		}
	} catch(e) {
		return null;
	}
}
