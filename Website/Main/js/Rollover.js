function smartRollover() {
	if(document.getElementsByTagName) {
		var images = document.getElementsByTagName("img");
		for(var i=0; i < images.length; i++) {
			if(images[i].getAttribute("src").match("374431twon."))
			{
				images[i].onmouseover = function() {
					this.setAttribute("src", this.getAttribute("src").replace("374431twon.", "336759twd."));
				}
				images[i].onmouseout = function() {
					this.setAttribute("src", this.getAttribute("src").replace("336759twd.", "374431twon."));
				}
			}
		}
	}
}

function smartRollover() {
	if(document.getElementsByTagName) {
		var images = document.getElementsByTagName("img");
		for(var i=0; i < images.length; i++) {
			if(images[i].getAttribute("src").match("755642fbon."))
			{
				images[i].onmouseover = function() {
					this.setAttribute("src", this.getAttribute("src").replace("755642fbon.", "258460fbd."));
				}
				images[i].onmouseout = function() {
					this.setAttribute("src", this.getAttribute("src").replace("258460fbd.", "755642fbon."));
				}
			}
		}
	}
}

if(window.addEventListener) {
			window.addEventListener("load", smartRollover, false);
		}
		else if(window.attachEvent) {
			window.attachEvent("onload", smartRollover);
		}