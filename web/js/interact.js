function add_code(lines) {
    var oldcode = $('#actions').val();
    var oldlines = oldcode.split('\n');
    var indent = null;
    var lastline;
    for (lastline = oldlines.length - 1; lastline >= 0; lastline--) {
        var match = oldlines[lastline].match(/^(\s+)\}?$/); 
        if (match)
            indent = match[1];
        else
            break;
    }

    var newlines = lines.split('\n');
    if (indent != null) {
        for (var ii in newlines)
            newlines[ii] = indent + '  ' + newlines[ii];
    }
    oldlines = oldlines.slice(0, lastline).concat(newlines, oldlines.slice(lastline));
    
    $('#actions').val(oldlines.join('\n'));
}