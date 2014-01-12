var state = {stack: []};
var async_waittime_ms = 60*1000;
var proc_id = Math.random().toString(36).substring(2);

function execute() {
    status("Evaluating...");
    eval($('#actions').val());

    while (state.stack.length > 0)
        (state.stack.pop())();

    if (typeof state.result == "string" || state.result instanceof $)
        $('#result').append(state.result);
    if (typeof state.result == "object")
        $('#result').append(state.result.join("\n"));
}

function rundebug() {
    status("Evaluating...");
    eval($('#actions').val());
}

function status(text) {
    $('#status').html(text);
}

// Sleep until state.async = false
function sleep_async() {
    var startTime = new Date().getTime();

    while (state.async && ((new Date()).getTime() - startTime < async_waittime_ms)) {
        $.ajax({
            url: "ss/wait.html",
            async: false,
            data: {
                us: 250*1000,
                proc: proc_id
            },
            success: function(data) {
                if (data == "CANCEL")
                    throw "User Canceled";
            }
        });
    }

    if (state.async)
        throw "Loading timeout!";
}

// Note that this function needs a sequence system
//   where each user function adds to the sequence, then executes
function load(url, options) {
    url = url || state.result;

    status("Getting " + url);
    state.async = true;
    $('#iframe').load(function() {
        $('#iframe').contents().ready(function() {
            state.async = false;
            state.result = state.htmls = state.doc = $('#iframe').contents();
            var cookie = $('#iframe').contents().find('#wget_cookie').html();
            if (cookie)
                state.cookie = cookie;
            status("Success");
            $('#with_load').show();
        });
    });
    
    if (url.indexOf("ss/") == 0)
        $('#iframe').attr({src: url});
    else
        $('#iframe').attr({src: localurl(url, options)});

    sleep_async();
}

function get(url) {
    try {
        url = url || state.result;

        if (typeof url == "string") {
            status("Getting " + url);
            $.ajax({
                url: localurl(url),
                dataType: 'html',
                async: false,
                error: function(xhr, status) {
                    throw "get error: " + status;
                },
                success: function(data) {
                    status("Success");
                    state.result = state.htmls = state.doc = data;
                    var cookie = $(data).find('#wget_cookie').html();
                    if (cookie)
                        state.cookie = cookie;
                }});

            return state.result;
        } else if (url instanceof Array) {
            ii = 0;
            while (!url[ii])
                ii++;
            state.stack.push(function() {
                get(url.slice(ii+1))
            });
            return get(url[ii]);
        } else
            alert("get: Unknown argument");
    } catch (err) {
        alert("Error: " + err.message);
    }
}

function reset() {
    state.htmls = $('#iframe').contents();
}

function find(selector, html) {
    status("Finding " + selector);
    html = html || state.htmls;
    state.result = state.htmls = $(html).find(selector);
    if (state.htmls.length > 0 && state.htmls[0].tagName == "FORM")
        state.form = state.htmls[0];
    return state.result;
}

function click_load($objs) {
    status("Clicking on object");
    $objs = $objs || state.htmls;

    var beforeloc = frames['iframe'].location.href;
    $(frames['iframe']).load(function() {
        state.async = false;
        state.result = state.htmls = state.doc = $('#iframe').contents();
        /*var afterloc = frames['iframe'].location.href;
        // Load this through load
        load(afterloc);*/
    });
    $objs.click();
    state.async = true;
    sleep_async();
}

function attr(name, $objs) {
    status("Extracting attribute " + name);
    $objs = $objs || state.htmls;
    
    var attrs = [];
    $objs.each(function(index, obj) {
        attrs[index] = $(obj).attr(name);
    });

    return state.result = state.texts = attrs;
}

function text($objs) {
    status("Extracting text");
    $objs = $objs || state.htmls;

    var texts = [];
    $objs.each(function(index, obj) {
        texts[index] = $(obj).text();
    });

    return state.result = state.texts = texts;
}

function replace(regex, str, subject) {
    status("Replacing with " + str);
    subject = subject || state.texts;

    if (typeof subject == "string")
        return state.result = subject.replace(regex, str);
    if (typeof subject == "object")
        return state.result = $.map(subject, function(elt) {
            return elt.replace(regex, str);
        });
}

// Manipulate forms
function val(selector, data) {
    $(selector).val(data);
}

function select(option) {
    $(option).parent().val($(option).attr('value'));
}

function click(selector) {
    status("Clicking on selector");
    $(frames['iframe']).load(function() {
            state.async = false;
        });

    $('#iframe').contents().find(selector).click();
    state.async = true;
    sleep_async();
}

function submit(selector) {
    $('#iframe').contents().find(selector).closest('form').submit();
}

// Producing the result

function addrow(id) {
    id = id || state.texts;
    $('#result').append("\n" + id);
}

function addcol(datum) {
    datum = datum || state.texts;
    
    if (datum.indexOf(',') != -1 || datum.indexOf('"') != -1)
        datum = '"' + datum.replace('"', '\\"') + '"';

    $('#result').append("," + datum);
}

function addinputs_header(htmls) {
    htmls = htmls || state.htmls;
    htmls = $(htmls).find(':input');

    state.input_columns = []
    htmls.each(function() {
        addcol($(this).attr('name'));
        state.input_columns.push($(this).attr('name'));
      });
}

function addinputs(htmls) {
    htmls = htmls || state.htmls;
    htmls = $(htmls).find(':input');

    var values = {}
    htmls.each(function() {
        var val = $(this).val();
        if (!val)
            val = "NA";

        values[$(this).attr('name')] = $(this).val();
    });

    for (var ii = 0; ii < state.input_columns.length; ii++) {
        if (values[state.input_columns[ii]])
            addcol(values[state.input_columns[ii]]);
        else
            addcol("NA");
    }
}

function append(data) {
    try {
        data = data || state.result;

        $('#result').append(data);
    } catch (err) {
        alert("Error: " + err.message);
    }
}

function post(obj, data) {
    obj = obj || state.result;

    if (obj instanceof $) {
        $form = obj.closest('form');
        var url = $form.attr('action');
        var data = $form.serializeArray();
        if (obj.is('input[type=submit]'))
            data.push({name: obj.attr('name'), value: obj.attr('value')});
        post(url, data);
    } else if (typeof obj == "string" && data) {
        status("Posting to " + obj);
        if (state.cookie)
            obj = posturl(obj, state.cookie);

        $.ajax({
            type: 'POST',
            url: obj,
            data: data,
            async: false,
            error: function(xhr, status) {
                throw "post error: " + status;
            },
            success: function(data) {
                status("Success");
                state.result = state.htmls = state.doc = data;
                $('#iframe').contents().html(state.doc);
                var cookie = $(data).find('#wget_cookie').html();
                if (cookie)
                    state.cookie = cookie;
            }});
    }
}

function postload(obj, data) {
    obj = obj || state.result;

    if (obj instanceof $) {
        $form = obj.closest('form');
        var url = $form.attr('action');
        var data = $form.serializeArray();
        if (obj.is('input[type=submit]'))
            data.push({name: obj.attr('name'), value: obj.attr('value')});
        postload(url, data);
    } else if (typeof obj == "string" && data)
        load(posturl(obj, state.cookie, data));
}

function extract_table(sep, transpose, obj) {
    obj = obj || state.htmls;
    sep = sep || ",";
    
    if (transpose) {
        var data = [];
        $data = $(obj).find('tr').each(function(ii) {
            $(this).find('td, th').map(function(jj) {
                if (!data[jj])
                    data[jj] = [];
                data[jj][ii] = $(this).text();
            });
        });

        for (var ii in data)
            data[ii] = data[ii].join(sep);
        
        data = data.join("\n");
    } else {
        $data = $(obj).find('tr').map(function() {
            var $line = $(this).find('td, th').map(function() { return $(this).text(); });
            return $.makeArray($line).join(sep);
        });
    
        var data = $.makeArray($data).join("\n");
    }

    $('#result').append(data + "\n");
    return data;
}



// DOES NOT WORK:
//   jquery can't find the script tags, even if dataType = text
function xhtml_translate(html, base) {
    // TODO: respect baseurl tag
    $obj = $(html);

    var baseurl = new URI(base);
    $obj.find('*[src]').each(function() {
        var oldurl = new URI($(this).attr('src'));
        $(this).attr('src', oldurl.resolve(baseurl));
    });

    return $obj;
}
