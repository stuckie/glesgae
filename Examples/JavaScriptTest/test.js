window = this;

screen = {
	availWidth: 800,
	availHeight: 480
};

navigator = {
	userAgent: "GLESGAE"
};

HTMLElement = function( tagName ){ 
	this.tagName = tagName;
	this.children = [];
};

HTMLElement.prototype.appendChild = function( element ) {
	this.children.push( element );
	
	if( element.tagName == 'script' ) {
	}
};

document = {
	location: { href: 'index' },
	
	head: new HTMLElement( 'head' ),
	body: new HTMLElement( 'body' ),
	
	createElement: function( name ) {
		if( name == 'canvas' ) {
			return new glesgae.Canvas();
		}
		return new HTMLElement( 'script' );
	},
	
	getElementById: function( id ) {
		return null;
	},
	
	getElementsByTagName: function( tagName ) {
		if( tagName == 'head' ) {
			return [document.head];
		}
	},
	
	addEventListener: function( type, callback ) {
		if( type == 'DOMContentLoaded' ) {
		}
	}
};

setTimeout = function(cb, t){ return Timer.setTimeout(cb, t); };
setInterval = function(cb, t){ return Timer.setInterval(cb, t); };
clearTimeout = function(id){ return Timer.clearTimeout(id); };
clearInterval = function(id){ return Timer.clearInterval(id); };

addEventListener = function( type, callback ){};

var title = new Image();
title.src = "Data/Texture.png";

var canvas = document.createElement('canvas');
canvas.width = 480;
canvas.height = 320;
var context2D = canvas.getContext('2d');
var keyboard = Input.getKeyboard(0);
context2D.drawImage(title, 0, 0);
var image = context2D.getImageData(0, 0, 256, 256);
for (var i = 0; i < 256 * 256 * 4; ++i)
	image.data[i] = 150;
setInterval(function() {	
	context2D.drawImage(title, 0, 0);
	if (keyboard.getKey(59) != 0.0) {
		context2D.putImageData(image, 1, 0);
	}
//	image = context2D.getImageData(0, 0, 256, 256);
	context2D.refresh();
}, 1000/60);
