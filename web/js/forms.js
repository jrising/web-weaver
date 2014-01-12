function display_form(form) {
    $(form).find(':input').each(function() {
        $elt = $(this);
        if ($elt.attr('type') == 'button' || $elt.attr('type') == 'submit')
            return;

        $elt.removeAttr('onclick');

        var options = '';
        if ($elt.attr('type') == 'text')
            options += form_dateloop_html($elt.attr('name'));

        if ($elt.attr('type') == 'hidden')
            $elt = $('<input type="text" name="' + $elt.attr('name') + '" + value="' + $elt.val() + '" />');
            
        $('#form_fields').append('<tr><td>' + $elt.attr('name') + '</td><td>' + $elt.clone().wrap('<div>').parent().html() + '</td><td>' + options + '</td></tr>');
    });
}

function form_dateloop_html(name) {
    return '<input type="button" value="Date Loop" onclick="return form_dateloop_setup(\'' + name + '\');" />';
}

function form_dateloop_setup(name) {
    var dateformat = prompt("Enter a date format according to http://docs.jquery.com/UI/Datepicker/formatDate:", "yy-mm-dd");
    var startdate = $.datepicker.parseDate(dateformat, prompt("Enter the earliest date:"));
    var enddate = $.datepicker.parseDate(dateformat, prompt("Enter the final date:"));
    $('#form_fields').find(':input[name=' + name + ']').replaceWith($.datepicker.formatDate(dateformat, startdate) + " - " + $.datepicker.formatDate(dateformat, enddate));

    add_code('for (var date = new Date(' + startdate.getTime() + '); date <= new Date(' + enddate.getTime() + '); date = new Date(date.getTime() + 24*60*60*1000)) {\n  $(state.form).find(":input[name=' + name + ']").val($.datepicker.formatDate("' + dateformat + '", date));\n}');
    $(state.form).find(":input[name=" + name + "]").val($.datepicker.formatDate(dateformat, startdate));
}

function add_form_submit_load() {
    add_code("click_load(find_submit(state.form));");
    click_load(find_submit(state.form));
}

function find_submit(form) {
    var submits = $(state.form).find(':submit');
    if (submits.length == 0)
        submits = $(state.form).find(':input[type=button]');
    return $(submits[submits.length - 1]);
}
