// test Node-Red node

function SampleNode(config) {
    RED.nodes.createNode(this,config);
    // node-specific code goes here
	let node = this;
	this.on('input', function(msg, send, done) {
		// For maximum backwards compatibility, check that send exists.
		// If this node is installed in Node-RED 0.x, it will need to
		// fallback to using `node.send`
		send = send || function() { node.send.apply(node,arguments) }

		// do something with 'msg'
		msg.payload = "hi";
		
		// send output
		send(msg);

		// If an error is hit, report it to the runtime
		if (err) {
			if (done) {
				// Node-RED 1.0 compatible
				done(err);
			} else {
				// Node-RED 0.x compatible
				node.error(err, msg);
			}
		}
	});
}

RED.nodes.registerType("sample",SampleNode, {
    settings: {
        sampleNodeColour: {
            value: "red",
            exportable: true
        }
    }
);