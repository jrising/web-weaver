function add_texts(texts) {
    status("Extracting text");
    texts = texts || state.texts;

    for (var ii in texts)
        addcol(texts[ii]);
}