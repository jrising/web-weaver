from BeautifulSoup import BeautifulSoup
import re

### Sizzle CSS Selector Engine
# Copyright 2011, The Dojo Foundation
# Released under the MIT, BSD, and GPL Licenses.
# More information: http://sizzlejs.com/
# Translated by me.

class Sizzle:
    def __init__(self, html):
        self.soup = BeautifulSoup(html)
        self.byid = re.compile(r'^#(?:/([\w\W]+)/$|([\w\-]*)$)')
        self.chunker = re.compile(r'((?:\((?:\([^()]+\)|[^()]+)+\)|\[(?:\[[^\[\]]*\]|['"][^'"]*['"]|[^\[\]'"]+)+\]|\\.|[^ >+~,(\[\\]+)+|[>+~])(\s*,\s*)?((?:.|\r|\n)*)') #"
        self.done = 0
        self.hasDuplicate = false
        self.baseHasDuplicate = true
        self.rBackslash = r'\\'
        self.rNonWord = r'\W'

        # Here we check if the JavaScript engine is using some sort of
        # optimization where it does not always call our comparision
        # function. If that is the case, discard the hasDuplicate value.
        [0, 0].sort(lambda x, y: baseHasDuplicate = false; return 0)

   def find_selector(selector):
        if not selector:
            return []
        match = byid.findall(selector)
        if match:
            if match[1]:
                return self.soup.findAll(id=re.compile(match[1]))
            if match[2]:
                return self.soup.findAll(id=match[2])
            return self.soup.findAll(id=True) # match everything with an id

        results = []

    def find(expr, context, isXML):
        set = []

        if not expr:
            return []

        for ii in range(Expr.order.length):
            var match,
            type = Expr.order[i];
        
        if ( (match = Expr.leftMatch[ type ].exec( expr )) ) {
            var left = match[1];
            match.splice( 1, 1 );

            if ( left.substr( left.length - 1 ) !== "\\" ) {
                match[1] = (match[1] || "").replace( rBackslash, "" );
                set = Expr.find[ type ]( match, context, isXML );

                if ( set != null ) {
                    expr = expr.replace( Expr.match[ type ], "" );
                    break;
                }
            }
        }
    }

    if ( !set ) {
        set = typeof context.getElementsByTagName !== "undefined" ?
            context.getElementsByTagName( "*" ) :
            [];
    }

    return { set: set, expr: expr };

    @staticmethod
    def root(selector, context, results, seed):
        # XXX: This is the Sizzle() function.  Need to define it!
        pass

class ExprFunctions:
    @staticmethod
    def relative_plus(checkSet, part):
        ## var isPartStr = typeof part === "string",
        ##     isTag = isPartStr && !rNonWord.test( part ),
        ##     isPartStrNotTag = isPartStr && !isTag;
        ## if ( isTag ) {
        ##     part = part.toLowerCase();
        ## }
        ## for ( var i = 0, l = checkSet.length, elem; i < l; i++ ) {
        ##     if ( (elem = checkSet[i]) ) {
        ##         while ( (elem = elem.previousSibling) && elem.nodeType !== 1 ) {}

        ##         checkSet[i] = isPartStrNotTag || elem && elem.nodeName.toLowerCase() === part ?
        ##             elem || false :
        ##             elem === part;
        ##     }
        ## }
        ## if ( isPartStrNotTag ) {
        ##     Sizzle.filter( part, checkSet, true );
        ## }
        pass

    @staticmethod
    def relative_gt(checkSet, part):
        ## var elem,
        ##     isPartStr = typeof part === "string",
        ##     i = 0,
        ##     l = checkSet.length;
        ## if ( isPartStr && !rNonWord.test( part ) ) {
        ##     part = part.toLowerCase();
        ##     for ( ; i < l; i++ ) {
        ##         elem = checkSet[i];
        ##         if ( elem ) {
        ##             var parent = elem.parentNode;
        ##             checkSet[i] = parent.nodeName.toLowerCase() === part ? parent : false;
        ##         }
        ##     }
        ## } else {
        ##     for ( ; i < l; i++ ) {
        ##         elem = checkSet[i];
        ##         if ( elem ) {
        ##             checkSet[i] = isPartStr ?
        ##                 elem.parentNode :
        ##                 elem.parentNode === part;
        ##         }
        ##     }
        ##     if ( isPartStr ) {
        ##         Sizzle.filter( part, checkSet, true );
        ##     }
        ## }
        pass

    @staticmethod
    def relative_nada(checkSet, part, isXML):
        ## var elem,
        ##     isPartStr = typeof part === "string",
        ##     i = 0,
        ##     l = checkSet.length;
        ## if ( isPartStr && !rNonWord.test( part ) ) {
        ##     part = part.toLowerCase();
        ##     for ( ; i < l; i++ ) {
        ##         elem = checkSet[i];
        ##         if ( elem ) {
        ##             var parent = elem.parentNode;
        ##             checkSet[i] = parent.nodeName.toLowerCase() === part ? parent : false;
        ##         }
        ##     }
        ## } else {
        ##     for ( ; i < l; i++ ) {
        ##         elem = checkSet[i];
        ##         if ( elem ) {
        ##             checkSet[i] = isPartStr ?
        ##                 elem.parentNode :
        ##                 elem.parentNode === part;
        ##         }
        ##     }
        ##     if ( isPartStr ) {
        ##         Sizzle.filter( part, checkSet, true );
        ##     }
        ## }
        pass

    @staticmethod
    def relative_not(checkSet, part, isXML):
        ## var nodeCheck,
        ##     doneName = done++,
        ##     checkFn = dirCheck;
        ## if ( typeof part === "string" && !rNonWord.test( part ) ) {
        ##     part = part.toLowerCase();
        ##     nodeCheck = part;
        ##     checkFn = dirNodeCheck;
        ## }
        ## checkFn( "previousSibling", part, doneName, checkSet, nodeCheck, isXML );
        pass

    @staticmethod
    def find_id(match, context, isXML):
        return context.findAll(id=match[1])

    @staticmethod
    def find_name(match, context):
        return context.findAll(name=match[1])

    @staticmethod
    def find_tag(match, context):
        return context.findAll(match[1])

    @staticmethod
    def prefilter_class(match, curLoop, inplace, result, bnot, isXML):
        match = " " + match[1].replace( rBackslash, "" ) + " "

        if isXML:
            return match

        i = 0
        while curLoop[i] is not None:
            if curLoop[i]:
                elem = curLoop[i]
                if bnot ^ (elem['class'] and re.sub('[\t\n\r]', ' ', " " + elem['class'] + " ").find(match) >= 0):
                    if not inplace:
                        result.push(elem)
                else if inplace:
                    curLoop[i] = False
            i += 1

        return false;

    @staticmethd
    def prefilter_child(match):
        ## if ( match[1] === "nth" ) {
        ##     if ( !match[2] ) {
        ##         Sizzle.error( match[0] );
        ##     }
        ##     match[2] = match[2].replace(/^\+|\s*/g, '');
        ##     # parse equations like 'even', 'odd', '5', '2n', '3n+2', '4n-1', '-n+6'
        ##     var test = /(-?)(\d*)(?:n([+\-]?\d*))?/.exec(
        ##         match[2] === "even" && "2n" || match[2] === "odd" && "2n+1" ||
        ##         !/\D/.test( match[2] ) && "0n+" + match[2] || match[2]);
        ##     # calculate the numbers (first)n+(last) including if they are negative
        ##     match[2] = (test[1] + (test[2] || 1)) - 0;
        ##     match[3] = test[3] - 0;
        ## }
        ## else if ( match[2] ) {
        ##     Sizzle.error( match[0] );
        ## }
        ## # TODO: Move to normal caching system
        ## match[0] = done++;
        ## return match;
        pass

    @staticmethod
    def prefilter_attr(match, curLoop, inplace, result, bnot, isXML):
        name = match[1] = re.sub(r'\\', '', match[1])
            
        if not isXML and Expr['attrMap'][name]:
            match[1] = Expr['attrMap'][name]

        # Handle if an un-quoted value was used
        match[4] = re.sub(r'\\', '', match[4] or match[5] or '')

        if match[2] == "~=":
            match[4] = " " + match[4] + " ";

        return match;

    @staticmethod
    def prefilter_pseudo(match, curLoop, inplace, result, bnot):
        ## if ( match[1] === "not" ) {
        ##     # If we're dealing with a complex expression, or a simple one
        ##     if ( ( chunker.exec(match[3]) || "" ).length > 1 || /^\w/.test(match[3]) ) {
        ##         match[3] = Sizzle(match[3], null, null, curLoop);
        ##     } else {
        ##         var ret = Sizzle.filter(match[3], curLoop, inplace, true ^ not);
        ##         if ( !inplace ) {
        ##             result.push.apply( result, ret );
        ##         }
        ##         return false;
        ##     }
        ## } else if ( Expr.match.POS.test( match[0] ) || Expr.match.CHILD.test( match[0] ) ) {
        ##     return true;
        ## }
        ## return match;
        pass

    @staticmethod
    def prefilter_pos(match):
        match.insert(0, True)
        return match

    @staticmethod
    def filters_text(elem):
        return elem.name.lower() == 'input' and elem['type'] == 'text'

Expr = Sizzle.selectors = {
    'order': [ "ID", "NAME", "TAG" ],

    'match': {
        'ID': re.compile(r'#((?:[\w\u00c0-\uFFFF\-]|\\.)+)'),
        'CLASS': re.compile(r'\.((?:[\w\u00c0-\uFFFF\-]|\\.)+)'),
        'NAME': re.compile(r'\[name=['"]*((?:[\w\u00c0-\uFFFF\-]|\\.)+)['"]*\]'),
        'ATTR': re.compile(r'\[\s*((?:[\w\u00c0-\uFFFF\-]|\\.)+)\s*(?:(\S?=)\s*(?:(['"])(.*?)\3|(#?(?:[\w\u00c0-\uFFFF\-]|\\.)*)|)|)\s*\]'),
        'TAG': re.compile(r'^((?:[\w\u00c0-\uFFFF\*\-]|\\.)+)'),
        'CHILD': re.compile(r':(only|nth|last|first)-child(?:\(\s*(even|odd|(?:[+\-]?\d+|(?:[+\-]?\d*)?n\s*(?:[+\-]\s*\d+)?))\s*\))?'),
        'POS': re.compile(r':(nth|eq|gt|lt|first|last|even|odd)(?:\((\d*)\))?(?=[^\-]|$)'),
        'PSEUDO': re.compile(r':((?:[\w\u00c0-\uFFFF\-]|\\.)+)(?:\((['"]?)((?:\([^\)]+\)|[^\(\)]*)+)\2\))?')
    }, #"

    'leftMatch': {},

    'attrMap': {
        "class": "className",
        "for": "htmlFor"
    },

    'attrHandle': {
        'href': lambda elem: elem.getAttribute("href"),
        'type': lambda elem: elem.getAttribute("type"),
    },

    'relative': {
        "+": ExprFunctions.relative_plus,
        ">": ExprFunctions.relative_gt,
        "": ExprFunctions.relative_nada,
        "~": ExprFunctions.relative_not
    },

    'find': {
        'ID': ExprFunctions.find_id,
        'NAME': ExprFunctions.find_name,
        'TAG': ExprFunctions.find_tag
    },

    'preFilter': {
        'CLASS': ExprFunctions.prefilter_class,
        'ID': lambda match: re.sub(r'\\', '', match[1]),
        'TAG': lambda match: re.sub(r'\\', '', match[1]).lower(),
        'CHILD': ExprFunctions.prefilter_child,
        'ATTR': ExprFunctions.prefilter_attr,
        'PSEUDO': ExprFunctions.prefilter_pseudo,
        'POS': ExprFunctions.prefilter_pos
    },
    
    'filters': {
        'enabled': lambda elem: not elem['disabled'] and elem['type'] != "hidden",
        'disabled': lambda elem: elem['disabled'],
        'checked': lambda elem: elem['checked'],
        'selected': lambda elem: elem['selected'],
        'parent': lambda elem: not not elem.contents,
        'empty': lambda elem: not elem.contents,
        'has': lambda elem, i, match: not not Sizzle.root(match[3], elem).length,
        'header': lambda elem: re.search(r'h\d', elem.name)
        'text': ExprFunctions.filters_text,
        'radio': lambda elem: elem.name.lower() == 'input' and elem['type'] == 'radio',
        'checkbox': lambda elem: elem.name.lower() == 'input' and elem['type'] == 'checkbox',
        'file': lambda elem: elem.name.lower() == 'input' and elem['type'] == 'file',
        'password': lambda elem: elem.name.lower() == 'input' and elem['type'] == 'password',
        'submit': lambda elem: elem.name.lower() in ['input', 'button'] and elem['type'] == 'submit',
        'image': lambda elem: 
            return elem.nodeName.toLowerCase() === "input" && "image" === elem.type;
        },

        'reset': lambda elem: 
            var name = elem.nodeName.toLowerCase();
            return (name === "input" || name === "button") && "reset" === elem.type;
        },

        'button': lambda elem: 
            var name = elem.nodeName.toLowerCase();
            return name === "input" && "button" === elem.type || name === "button";
        },

        'input': lambda elem: 
            return (/input|select|textarea|button/i).test( elem.nodeName );
        },

        'focus': lambda elem: 
            return elem === elem.ownerDocument.activeElement;
        }
    },
    'setFilters': {
        'first': lambda elem, i: 
            return i === 0;
        },

        'last': lambda elem, i, match, array: 
            return i === array.length - 1;
        },

        'even': lambda elem, i: 
            return i % 2 === 0;
        },

        'odd': lambda elem, i: 
            return i % 2 === 1;
        },

        'lt': lambda elem, i, match: 
            return i < match[3] - 0;
        },

        'gt': lambda elem, i, match: 
            return i > match[3] - 0;
        },

        'nth': lambda elem, i, match: 
            return match[3] - 0 === i;
        },

        'eq': lambda elem, i, match: 
            return match[3] - 0 === i;
        }
    },
    'filter': {
        'PSEUDO': function( elem, match, i, array ) {
            var name = match[1],
                filter = Expr.filters[ name ];

            if ( filter ) {
                return filter( elem, i, match, array );

            } else if ( name === "contains" ) {
                return (elem.textContent || elem.innerText || Sizzle.getText([ elem ]) || "").indexOf(match[3]) >= 0;

            } else if ( name === "not" ) {
                var not = match[3];

                for ( var j = 0, l = not.length; j < l; j++ ) {
                    if ( not[j] === elem ) {
                        return false;
                    }
                }

                return true;

            } else {
                Sizzle.error( name );
            }
        },

        'CHILD': function( elem, match ) {
            var type = match[1],
                node = elem;

            switch ( type ) {
                case "only":
                case "first":
                    while ( (node = node.previousSibling) )  {
                        if ( node.nodeType === 1 ) { 
                            return false; 
                        }
                    }

                    if ( type === "first" ) { 
                        return true; 
                    }

                    node = elem;

                case "last":
                    while ( (node = node.nextSibling) )  {
                        if ( node.nodeType === 1 ) { 
                            return false; 
                        }
                    }

                    return true;

                case "nth":
                    var first = match[2],
                        last = match[3];

                    if ( first === 1 && last === 0 ) {
                        return true;
                    }
                    
                    var doneName = match[0],
                        parent = elem.parentNode;
    
                    if ( parent && (parent.sizcache !== doneName || !elem.nodeIndex) ) {
                        var count = 0;
                        
                        for ( node = parent.firstChild; node; node = node.nextSibling ) {
                            if ( node.nodeType === 1 ) {
                                node.nodeIndex = ++count;
                            }
                        } 

                        parent.sizcache = doneName;
                    }
                    
                    var diff = elem.nodeIndex - last;

                    if ( first === 0 ) {
                        return diff === 0;

                    } else {
                        return ( diff % first === 0 && diff / first >= 0 );
                    }
            }
        },

        'ID': function( elem, match ) {
            return elem.nodeType === 1 && elem.getAttribute("id") === match;
        },

        'TAG': function( elem, match ) {
            return (match === "*" && elem.nodeType === 1) || elem.nodeName.toLowerCase() === match;
        },
        
        'CLASS': function( elem, match ) {
            return (" " + (elem.className || elem.getAttribute("class")) + " ")
                .indexOf( match ) > -1;
        },

        'ATTR': function( elem, match ) {
            var name = match[1],
                result = Expr.attrHandle[ name ] ?
                    Expr.attrHandle[ name ]( elem ) :
                    elem[ name ] != null ?
                        elem[ name ] :
                        elem.getAttribute( name ),
                value = result + "",
                type = match[2],
                check = match[4];

            return result == null ?
                type === "!=" :
                type === "=" ?
                value === check :
                type === "*=" ?
                value.indexOf(check) >= 0 :
                type === "~=" ?
                (" " + value + " ").indexOf(check) >= 0 :
                !check ?
                value && result !== false :
                type === "!=" ?
                value !== check :
                type === "^=" ?
                value.indexOf(check) === 0 :
                type === "$=" ?
                value.substr(value.length - check.length) === check :
                type === "|=" ?
                value === check || value.substr(0, check.length + 1) === check + "-" :
                false;
        },

        'POS': function( elem, match, i, array ) {
            var name = match[2],
                filter = Expr.setFilters[ name ];

            if ( filter ) {
                return filter( elem, i, match, array );
            }
        }
    }
};
