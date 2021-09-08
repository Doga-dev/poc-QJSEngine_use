// test2.js

// slider is used to define the duration in tenth of second of the execution
var duration;
// name of the variable that contains the progression value
var progess = "result";


function setDuration(value) {
  if (duration != value) {
    duration = value;
    print("duration = " + (duration / 10.0) + " s");
  }
};

var res = 0;
for(let i = 0; i < 100 ; i++) {
  setDuration(AppAPI.getValue("slider"));
  AppAPI.delay(duration);
  AppAPI.setValue(progess, i);
}
print("Done");
