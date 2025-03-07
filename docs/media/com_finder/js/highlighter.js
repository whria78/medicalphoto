var Highlighter = new Class({
	options: {
		autoUnhighlight: true,
		caseSensitive: false,
		startElement: false,
		endElement: false,
		elements: new Array(),
		className: 'highlight',
		onlyWords: true,
		tag: 'span'
	},
	initialize: function (options) {
		this.setOptions(options);
		this.getElements(this.options.startElement, this.options.endElement);
		this.words = [];
	},
	highlight: function (words) {
		if (words.constructor === String) {
			words = [words];
		}
		if (this.options.autoUnhighlight) {
			this.unhighlight(words);
		}
		var pattern = this.options.onlyWords ? '\b' + pattern + '\b' : '(' + words.join('\\b|\\b') + ')';
		var regex = new RegExp(pattern, this.options.caseSensitive ? '' : 'i');
		this.options.elements.each(function (el) {
			this.recurse(el, regex, this.options.className);
		}, this);
		return this;
	},
	unhighlight: function (words) {
		if (words.constructor === String) {
			words = [words];
		}
		words.each(function (word) {
			word = (this.options.caseSensitive ? word : word.toUpperCase());
			if (this.words[word]) {
				var elements = $$(this.words[word]);
				elements.setProperty('class', '');
				elements.each(function (el) {
					var tn = document.createTextNode(el.getText());
					el.getParent().replaceChild(tn, el);
				});
			}
		}, this);
		return this;
	},
	recurse: function (node, regex, klass) {
		if (node.nodeType === 3) {
			var match = node.data.match(regex);
			if (match) {
				var highlight = new Element(this.options.tag);
				highlight.addClass(klass);
				var wordNode = node.splitText(match.index);
				wordNode.splitText(match[0].length);
				var wordClone = wordNode.cloneNode(true);
				highlight.appendChild(wordClone);
				wordNode.parentNode.replaceChild(highlight, wordNode);
				highlight.setProperty('rel', highlight.get('text'));
				var comparer = highlight.get('text');
				if (!this.options.caseSensitive) {
					comparer = highlight.get('text').toUpperCase();
				}
				if (!this.words[comparer]) {
					this.words[comparer] = [];
				}
				this.words[comparer].push(highlight);
				return 1;
			}
		} else if ((node.nodeType === 1 && node.childNodes) && !/(script|style|textarea|iframe)/i.test(node.tagName) && !(node.tagName === this.options.tag.toUpperCase() && node.className === klass)) {
			for (var i = 0; i < node.childNodes.length; i++) {
				i += this.recurse(node.childNodes[i], regex, klass);
			}
		}
		return 0;
	},
	getElements: function (start, end) {
		var next = start.getNext();
		if (next.id != end.id) {
			this.options.elements.include(next);
			this.getElements(next, end);
		}
	}
});
Highlighter.implement(new Options);
window.addEvent('domready', function () {
	var start = document.id('highlighter-start');
	var end = document.id('highlighter-end');
	if (!start || !end || !window.highlight) {
		return true;
	}
	highlighter = new Highlighter({
		startElement: start,
		endElement: end,
		autoUnhighlight: true,
		onlyWords: false
	}).highlight(window.highlight);
	start.dispose();
	end.dispose();
});
