function total_words(text) {
    return text.split(/\b/m).length / 2;
}

function count_instances(text, word) {
    return text.match(new RegExp("\\b" + word.replace(/[-\/\\^$*+?.()|[\]{}]/g, '\\$&') + "\\b", "igm")).length;
}