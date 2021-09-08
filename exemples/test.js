// test.js

function runStep(inVar) {
	return (inVar * 2) % 100;
};


var n = AppAPI.getValue("slider");
print("n = " + n);
//var i = 2;
var res = 0;
for(let i = 0; i < 3 ; i++) {
	AppAPI.delay(200);
	res = (n + i * 15) % 100;
	print("res = " + res);
	AppAPI.setValue("result", res);
}
AppAPI.setValue("toto", res);

print("Done");
