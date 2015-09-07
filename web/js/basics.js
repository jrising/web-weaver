jQuery.fn.getPath = function() {
    if (this.length != 1) throw 'Requires one element.';

    var path, node = this;
    while (node.length) {
        var realNode = node[0], name = realNode.localName;
        if (!name) break;

        name = name.toLowerCase();
        if (realNode.id) {
            // As soon as an id is found, there's no need to specify more.
            return name + '#' + realNode.id + (path ? '>' + path : '');
        } else if (realNode.className) {
            name += '.' + realNode.className.split(/\s+/).join('.');
        }

        var parent = node.parent(), siblings = parent.children(name);
        if (siblings.length > 1) name += ':eq(' + siblings.index(node) + ')';
        path = name + (path ? '>' + path : '');

        node = parent;
    }

    return path;
};

jQuery.fn.getGeneralPath = function() {
    if (this.length != 1) throw 'Requires one element.';

    var path, node = this;
    while (node.length) {
        var realNode = node[0], name = realNode.localName;
        if (!name) break;

        name = name.toLowerCase();
        if (realNode.id && path) {
            // As soon as an id is found, there's no need to specify more.
            return name + '#' + realNode.id + (path ? '>' + path : '');
        } else if (realNode.className) {
            name += '.' + realNode.className.split(/\s+/).join('.');
        }

        var parent = node.parent(), siblings = parent.children(name);
        path = name + (path ? '>' + path : '');

        node = parent;
    }

    return path;
};

function ui_url() {
    var url = $(':input[name=url]').val();
    if (!(url.indexOf('http://') == 0) && !(url.indexOf('https://') == 0))
        url = 'http://' + url;
    return url;
}

function add_get() {
    var url = ui_url();
    $('#actions').val($('#actions').val() + 'get("' + url + '");\n');
    load(url); // don't get, so shows up
}

function add_load() {
    var url = ui_url();

    if ($(':input[name=load_noscript]').is(':checked')) {
        $('#actions').val($('#actions').val() + 'load("' + url + '", {noscript: true});\n');
        load(url, {noscript: true});
    } else {
        $('#actions').val($('#actions').val() + 'load("' + url + '");\n');
        load(url);
    }
}

function add_load_text() {
    if ($(':input[name=load_text_noscript]').is(':checked')) {
        $('#actions').val($('#actions').val() + 'load(result.text, {noscript: true});\n');
        load(state.texts[0], {noscript: true});
    } else {
        $('#actions').val($('#actions').val() + 'load(result.text);\n');
        load(state.texts[0]);
    }
}

function localurl(url, options) {
    options = options || {};

    var url = "ss/wget.html?ww_url=" + encodeURIComponent(url);
    if (options.noscript)
        url += '&ww_noscript=true';
    if (options.noxhtml)
        url += "&ww_noxhtml=true";
    if (options.noxform)
        url += "&ww_noxform=true";

    return url;
}

function posturl(url, cookie, post) {
    var url = "ss/wget.php?ww_url=" + encodeURIComponent(url) + "&ww_cookie=" + encodeURIComponent(cookie);
    if (post) {
        var postdata = "";
        for (var ii in post) {
            if (post[ii].name && post[ii].value)
                postdata += "&" + post[ii].name + "=" + encodeURIComponent(post[ii].value);
        }
        postdata = postdata.substr(1);
        url += "&ww_post=" + encodeURIComponent(postdata);
    }

    return url;
}

// Hover to identify an item
function identify_element(tag) {
    var $allelts;
    if (tag) 
        $allelts = $('#iframe').contents().find('html ' + tag);
    else
        $allelts = $('#iframe').contents().find('html *');

    $allelts.mouseover(function(event) {
        var $obj = $(this);

        $('#iframe').contents().find('.highlight').remove();
        highlight($obj);
        $obj.click(function(event) {
            $(':input[name=selector]').val($obj.getPath());
            event.stopPropagation();
            event.preventDefault();

            return false;
        });
        event.stopPropagation();
        event.preventDefault();
    });
    $allelts.mouseout(function() {
        $('#iframe').contents().find('.highlight').remove();
    });
}

// Hover to identify an item to define a set of items
function identify_element_all() {
    var $allelts = $('#iframe').contents().find('html *');
    $allelts.mouseover(function(event) {
        var $obj = $(this);

        $('#iframe').contents().find('.highlight').remove();

        highlight($('#iframe').contents().find($obj.getGeneralPath()));

        $obj.click(function(event) {
            $(':input[name=selector]').val($obj.getGeneralPath());
            event.stopPropagation();
            event.preventDefault();

            return false;
        });
        event.stopPropagation();
        event.preventDefault();
    });
    $allelts.mouseout(function() {
        $('#iframe').contents().find('.highlight').remove();
    });
}

function add_find() {
    var selector = $(':input[name=selector]').val();
    $('#actions').val($('#actions').val() + 'find("' + selector + '");\n');
    find(selector);

    if (state.htmls.length > 0) {
        if (state.htmls[0].tagName == "A")
            $(':input[name=attribute]').val("href");
        if (state.htmls[0].tagName == "INPUT")
            $(':input[name=attribute]').val('value');
    }

    var html = $.makeArray(state.htmls.wrap('<div>').parent().map(function() {
        return $(this).html();
    })).join("\n");

    state.result.unwrap();

    if (state.htmls.length > 0 && state.htmls[0].tagName == "FORM") {
        display_form(state.htmls[0]);
        $('#with_form').show();
    }
    else {
        $('#objects').text(html);
        $('#with_html').show();
    }
}

function show_identified() {
    var selector = $(':input[name=selector]').val();
    highlight($('#iframe').contents().find(selector));
}

function highlight($objs) {
    $objs.each(function(ii, obj) {
        var $obj = $(obj);
        var offset = $obj.offset();

        var $topline = highlight_line($obj);
        var $botline = highlight_line($obj);
        var $lftline = highlight_line($obj);
        var $rgtline = highlight_line($obj);
        
        offset.left -= 2;
        offset.top -= 2;
        $topline.offset(offset);
        $topline.width($obj.width());
        $topline.height(2);

        $lftline.offset(offset);
        $lftline.width(2);
        $lftline.height($obj.height());

        offset.left += $obj.width();
        $rgtline.offset(offset);
        $rgtline.width(2);
        $rgtline.height($obj.height());

        offset.left -= $obj.width();
        offset.top += $obj.height();
        $botline.offset(offset);
        $botline.width($obj.width());
        $botline.height(2);

        $obj.after($topline, $botline, $lftline, $rgtline);
    });
}

function highlight_line($obj) {
    var $line = $('<div class="highlight"></div>');
    $line.css({
        position: 'absolute',
        backgroundColor: 'red',
        //border: '2px solid red',
        zIndex: $obj.css('z-index') + 1
    });

    return $line;
}

function add_click_load($obj) {
    $('#actions').val($('#actions').val() + 'click_load();\n');
    click_load();
}

function add_text($obj) {
    $('#actions').val($('#actions').val() + 'text();\n');
    text();
    $('#objects').text(state.texts.join("\n"));
    $('#with_text').show();
}

function add_attr() {
    var name = $(':input[name=attribute]').val();
    $('#actions').val($('#actions').val() + 'attr("' + name + '");\n');
    attr(name);

    $('#objects').text(state.texts.join("\n"));
    $('#with_text').show();
}
