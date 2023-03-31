var DerivedClass = Module.Application.extend("Application", {
    // __construct and __destruct are optional.  They are included
    // in this example for illustration purposes.
    // If you override __construct or __destruct, don't forget to
    // call the parent implementation!
    __construct: function() {
        this.__parent.__construct.call(this);
        this.setup();
    },
	setup: function() {
    	console.log("setting up");
    	this.cube = new Module.Cube;
    	this.cube.setup();
        // your code goes here
    },
    __destruct: function() {
        this.__parent.__destruct.call(this);
    },
    draw: function() {
    	console.log("hello world!");
    	this.cube.draw();
        // your code goes here
    },
});

app = new DerivedClass;
Module.run(app);
