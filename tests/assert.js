(function(){

if (!Error.captureStackTrace) {
  throw new Error(
  'your browser doesn\'t support the v8-first stacktrace api. '+
  'Please search issues at github.com/devinrhode2/better-assert-browser/issues and '+
  'open an issue to support your browser if there isn\'t one open already. '+
  'Use chrome for better-assert-browser to work right now.')
}

/**
 * Module dependencies.
 */

function getRawStack() { //used to be called callsite (from visionmedia)

  //NORMALLY UNDEFINED!
  var orig = Error.prepareStackTrace

  //this is absolutely necessary, otherwise the stack is a regular string and lines 3,4,5 of assert will fail
  Error.prepareStackTrace = function(_, stack){ return stack }
  var err = new Error() //****
  Error.captureStackTrace(err, arguments.callee)
  var stack = err.stack

  //make sure we don't globally modify anything,
  //which could possibly affect other javascript:
  if (orig) {
    Error.prepareStackTrace = orig
  } else {
    delete Error.prepareStackTrace
  }

  return stack
}

function AssertionFailure(options) {
  //copied and modified from https://github.com/nodejs/node/blob/master/lib/assert.js#L44
  this.name = 'AssertionFailure'
  this.message = options.message
  Error.captureStackTrace(this, options.stackStartFunction)
}

function assert(expr) {
  if (expr) return
  var stack = getRawStack()
  var call = stack[1]
  var lineno = call.getLineNumber()

    throw (new AssertionFailure({
      message: expr.toString(),
      stackStartFunction: stack[0].getFunction()
    })).stack
}

/**
 * Expose `assert`.
 */

window.assert = window.NO_ASSERT ? function(){} : assert


})();
