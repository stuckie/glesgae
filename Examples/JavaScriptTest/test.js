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

addEventListener = function( type, callback ){};

var title = new Image();
title.src = "Data/Texture.png";

var canvas = document.createElement('canvas');
canvas.width = 800;
canvas.height = 480;
var context2D = canvas.getContext('2d');
context2D.drawImage(title, 0, 0);
context2D.refresh();