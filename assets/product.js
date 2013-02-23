$(document).ready(function() {
    // clean up empty date input
    // $('input[value="0001-01-01"]').val('');
    
    $(".datepicker").datepicker({ dateFormat: 'yy-mm-dd' });
    
    var postUpdate = function() {
        var data = {},
            captionPanel = $(this).parent().parent();
        captionPanel.find('input').each(function() {
            data[$(this).attr('name')] = $(this).val();
        });
        
        $.ajax('/product', {
            type: 'POST',
            data: data
        });
    };
    
    var updateImg = function() {
        var img = $(this).parent().parent().parent().find('img');
        img.attr('src', $(this).val());
        console.log("new PhotoLink: " + $(this).val());
    };
    
    var insertNewProductForm = function () {
        var templ = "<li class='span4'><form class='thumbnail'>\
            <img src=''>\
            <div class='caption'>\
                <div class='input-prepend'>\
                  <span class='add-on product-add-on'>Name</span>\
                  <input class='span2 product-input' type='text' name='name' value=''>\
                </div>\
                <div class='input-prepend'>\
                  <span class='add-on product-add-on'>Price</span>\
                  <input class='span2 product-input' type='number' name='price' value=''>\
                </div>\
                <div class='input-prepend'>\
                  <span class='add-on product-add-on'>PhotoLink</span>\
                  <input class='span2 product-input' type='text' name='photolink' value=''>\
                </div>\
                <div class='input-prepend'>\
                  <span class='add-on product-add-on'>From</span>\
                  <input class='span2 product-input datepicker' type='text' name='validfrom' value=''>\
                </div>\
                <div class='input-prepend'>\
                  <span class='add-on product-add-on'>To</span>\
                  <input class='span2 product-input datepicker' type='text' name='validto' value=''>\
                </div>\
                <div id='savingDevice'>\
                    <a class='btn btn-primary pull-right'>Save</a>\
                    <div style='clear:both;'></div>\
                </div>\
            </div>\
        </form></li>";
    
        var lastRow = $('#main-panel').find('ul').last(),
            lastRowAppendable = lastRow.find('li').length < 3;
        if (!lastRowAppendable) {
            lastRow.after("<div class='row-fluid'><ul class='thumbnails'></ul></div>");
            lastRow = $('#main-panel').find('ul').last();
        };
    
        lastRow.append(templ);
        var currentForm = lastRow.find('form').last();
        currentForm.find('input[name="photolink"]').bind('change', updateImg);
        $(".datepicker").datepicker({ dateFormat: 'yy-mm-dd' });
        // $(".datepicker").datepicker();
        // $(".datepicker").datepicker("option", "dateFormat", 'yy-mm-dd');
        
        lastRow.find('li').last().find('a').bind('click', function() {
            var data = {},
                captionPanel = $(this).parent().parent();
            captionPanel.find('input').each(function() {
                data[$(this).attr('name')] = $(this).val();
            });
        
            $.ajax('/product', {
                type: 'POST',
                data: data
            }).done(function(product) {
                captionPanel.prepend("<input type='hidden' name='productid' value='" + $.parseJSON(product).Id + "'>");
                $("#savingDevice").remove();
                currentForm.find('input').bind('change', postUpdate);
                
                insertNewProductForm();
            });
        });
    };
    
    $("input").bind('change', postUpdate);
    $('input[name="photolink"]').bind('change', updateImg);
    
    insertNewProductForm();
});