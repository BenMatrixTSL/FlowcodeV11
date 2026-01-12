// JavaScript Document
jQuery(document).ready(function(){
jQuery("img.a").hover(
function() {
jQuery(this).stop().animate({"opacity": "0"}, "slow");
},
function() {
jQuery(this).stop().animate({"opacity": "1"}, "slow");
}); 
});