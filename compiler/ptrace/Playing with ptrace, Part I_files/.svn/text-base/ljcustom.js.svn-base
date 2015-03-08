/* -- Menu ---------------------------------------------------------------- */

/* Menu = {
  init: function() {
    this.menus = $('#header_menubar li.expanded');
    this.menus.each(function() {
      $(this).bind("mouseover", function() { $(this).addClass('hover'); });
      $(this).bind("mouseout", function() { $(this).removeClass('hover'); });
    });
  }
};
*/
Menu = {
  init: function() {
		$('#header_menubar li.expanded').hover(function(){
			$(this).addClass("hover");
		},function(){
			$(this).removeClass("hover");
		});
  }
};


/* -- Carousel ------------------------------------------------------------ */

Carousel = {
  init: function() {
    this.articles = $('#carousel_articles div.article');
    this.listitems = $('#carousel_buttons li');
    this.lastselection = 0;
    
    // Add events to buttons
    $('#carousel_buttons a').each(function(i) {
      $(this).bind("mouseover", function() { Carousel.show(i); });
    });
    
    // Hide all articles minus the first
    this.articles.each(function(i) {
      if (i != 0) { $(this).hide(); }
    });
  },
  
  show: function(item) {
    if (item != this.lastselection)  {
      $(this.articles[this.lastselection]).fadeOut('fast');
      $(this.listitems[this.lastselection]).removeClass('active');
      $(this.articles[item]).fadeIn('fast');
      $(this.listitems[item]).addClass('active');
      this.lastselection = item;
    }
  }
};


/* -- Truncate paragraphs in home page ------------------------------------ */

/*Truncate = {
  init: function() {
    this.maxlength = 250;
    this.titlemultiplier = 2;
    this.articles = $('#content_body div.node div.content');
    
    this.articles.each(function(i){
      
      // Get full text
      var fullcontent = this.innerHTML;
      
      // Get truncated text
      var fulltext = fullcontent.replace(/<\/?[^>]+(>|$)/g, "");
      var paragraph = $(this).find('p:first')[0].innerHTML.replace(/<\/?[^>]+(>|$)/g, "");
      var title = $('#content_body div.node div.head h3 a')[i].innerHTML;
      var truncatedcontent = Truncate.truncate(fulltext, paragraph, title);

      if (truncatedcontent) {
        // Delete content text
        this.innerHTML = '';

        // Generate the two divs if needed
        $(this).append('<div class=\"full\">'+fullcontent+'<span class=""</div>');
        $(this).append('<div class=\"truncated\"><p>'+truncatedcontent+'</p></div>');
      
        // Add buttons
        $(this).find('div.full p:last').append('&nbsp;<a class=\"showtruncated\" href=\"javascript:;\" title=\"Click to hide exceeding text\"><img src=\"/images/node_contract.gif\" /></a>');
        $(this).find('div.truncated p:last').append('&nbsp;<a class=\"showfull\" href=\"javascript:;\" title=\"Click to show exceeding text\"><img src=\"/images/node_expand.gif\" /></a>');
      
        // Add actions to buttons
        $(this).find('a.showtruncated').click(function() { Truncate.contract(this); });
        $(this).find('a.showfull').click(function() { Truncate.expand(this); });
        
        // Hide full text
        Truncate.contract($(this).find('a.showtruncated'));
      };
      
    });
  },
  
  truncate: function(fulltext, paragraph, title) {
    var max = this.maxlength-(title.length*this.titlemultiplier);
    var chars = /\s/;
    
    if (fulltext.length > max) {
      while (max < fulltext.length) {
        c = paragraph.charAt(max);
        if (c.match(chars)) { return paragraph.substring(0,max); }
        max--;
      }
    }
    else { return false; }
  },
  
  expand: function(item) {
    $(item).parents('div.content').find('div.full').css('display', 'block');
    $(item).parents('div.content').find('div.truncated').css('display', 'none');
    return false;
  },
  
  contract: function(item) {
    $(item).parents('div.content').find('div.truncated').css('display', 'block');
    $(item).parents('div.content').find('div.full').css('display', 'none');
    return false;
  }
}
*/
/* -- Initialize ---------------------------------------------------------- */


$(document).ready(function() {
  Menu.init();
  if ($('carousel')) { Carousel.init(); };
  if ($('body.home div#content_body div.node').length > 0) { Truncate.init(); };
if ($('.panel-2col div#content_body div.node').length > 0) { Truncate.init(); };

});
