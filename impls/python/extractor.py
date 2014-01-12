from Tkinter import *
import tkFileDialog, tkSimpleDialog, tkMessageBox

class App:
    def __init__(self, master):
        """Initialize basic frame of console"""
        self.master = master
        self.masterframe = Frame(master)
        self.masterframe.grid(row=0, column=0)
        self.numboxes = 0
        self.numrows = 1
        self.numcolumns = 4
        self.boxes = []

        self.initiallocn = LabelFrame(self.masterframe, text="Initial Location")
        self.initiallocn.grid(row=0, column=0)

        Label(self.initiallocn, text="Initial URL: ").grid(row=0, column=0)
        self.initialurl = StringVar()
        urlentry = Entry(self.initiallocn, textvariable=self.initialurl, width=5)
        urlentry.grid(row=0, column=1)
        urlentry.insert(END, "http://")

        button = Button(self.initiallocn, text="Grab", command=self.grab)
        button.grid(row=1, column=0)
        button = Button(self.initiallocn, text="Quit", command=master.quit)
        button.grid(row=1, column=1)

        self.boxframe = Frame(self.masterframe, borderwidth=1)
        self.boxframe.grid(row=0, column=1, rowspan=4)        

        self.initializebox()

    def saveconfig(self, path=""):
        """Save current configuration into a file."""
        if not path:
            path = tkFileDialog.asksaveasfilename(defaultextension=".pkl", filetypes=[("Config files", ".pkl")], title="Save Configuration")
            if not path:
                return

        path = str(path)
        pickleobject = []
        for i,box in enumerate(self.boxes):
            pickleobject.append({})
            for key in box:                
                try:
                    pickleobject[-1][key] = box[key].get()
                except:
                    pass
            
        f = open(path, "wb")
        pickle.dump(pickleobject, f)

        pickle.dump(self.initialurl.get(), f)
        f.close()

    def loadconfig(self, path=""):
        """Load a configuration from a file."""
        if not path:
            path = tkFileDialog.askopenfilename(filetypes=[("Config files", ".pkl")], title="Open Configuration")
        if not path:
            return

        self.boxframe.destroy()
        self.numboxes = 0
        self.boxes = []
            
        self.boxframe = Frame(self.masterframe, borderwidth=1)
        self.boxframe.grid(row=0, column=1, rowspan=4)

        self.initializebox()

        f = open(path, "rb")
        pickleobject = pickle.load(f)

        for i, elem in enumerate(pickleobject):
            if i == 0:
                self.initialbox.destroy()
                self.createbox(0, 1, elem['vartype'])
            else:
                self.addnewbox(elem['vartype'])

            for key in elem:
                try: self.boxes[i][key].delete(0, END)
                except: pass
                try: self.boxes[i][key].insert(0, elem[key])
                except: pass
                try: self.boxes[i][key].set(elem[key])
                except: pass
                if elem[key] == 1:
                    try: self.boxes[i]["%scheck" % key].select()                            
                    except: pass
                    try: self.boxes[i]["%sCheck" % key].select()
                    except: pass

        try: self.initialurl.set(pickle.load(f))
        except: pass
        f.close()

    def initializebox(self):
        """Create the "load config..." button and "make variation >>" button
        when there are 0 panels"""
        def makefirstbox():
            self.initialbox.destroy()
            self.createbox(0)

        Button(self.boxframe, text="Load Configuration...", command=self.loadconfig).grid(row=0, column=0)
        self.initialbox = Frame(self.boxframe)
        self.initialbox.grid(row=1, column=0)

        self.startbutton = Button(self.initialbox, text="Add Processing >>", command=makefirstbox)
        self.startbutton.grid(row=0, column=0)

    def createbox(self, boxid, new=True, proctype="general"):
        """Create a new panel, or, recreate an old one if the algorithm
        is changed."""
        row = (boxid / self.numcolumns) + 1
        column = boxid % self.numcolumns
        if new:
            self.boxes.append({})
            self.boxes[-1]['frame'] = LabelFrame(self.boxframe, borderwidth=2, text="Group %d" % self.numboxes)
            self.boxes[-1]['frame'].grid(row=row,column=column, sticky=N)
            self.numboxes += 1

        box = self.boxes[boxid]

        if not new:
            savedoptions = [box['selector'].get()]
            box['frame'].destroy()
            box['frame'] = LabelFrame(self.boxframe, borderwidth=2, text="Group %d" % boxid)
            box['frame'].grid(row=row, column=column, sticky=N)

        box['selector'] = StringVar()
        labeltext = "Selector: "
        Label(box['frame'], text=labeltext).grid(row=2, sticky=E)
        entryname = "selectorentry"
        box[entryname] = Entry(box['frame'], textvariable=box['selector'], width=10)
        box[entryname].grid(row=2, column=1, sticky=W)

        if not new:
            box['selectorentry'].insert(0, savedoptions[0])

        box['proctype'] = StringVar(box['frame'])
        box['proctype'].set(proctype)
        action = lambda x=boxid: self.createbox(boxid, 0, box['proctype'].get())
        box['procmenu'] = OptionMenu(box['frame'], box['proctype'], "general", "form-fill", command=action)
        box['procmenu'].grid(row=0, column=0, sticky=W)

        if (boxid == self.numboxes-1 or new) and self.numboxes < self.numrows * self.numcolumns:
            box['newboxbutton'] = Button(box['frame'], text="Add another >>", command=self.addnewbox)
            box['newboxbutton'].grid(row=1000, column=0, columnspan=100)
        if new or boxid == self.numboxes-1:
            box['deletebutton'] = Button(box['frame'], text="<< Delete", command=self.deletebox)
            box['deletebutton'].grid(row=999, column=0, columnspan=100)

        if boxid == 0 and new:
            self.savebutton = Button(self.boxframe, text="Save Configuration...", command=self.saveconfig)
            self.savebutton.grid(row=10, column=0)

    def addnewbox(self, proctype='general'):
        """What to do when "Add Another >>" button is pressed to add
        a new panel"""
        self.boxes[-1]['newboxbutton'].destroy()
        if self.numboxes >= 1: self.boxes[-1]['deletebutton'].destroy()
        self.createbox(self.numboxes, True, proctype)

    def deletebox(self):
        """Delete the most recently created panel"""
        self.boxes[-1]['frame'].destroy()
        self.boxes.pop()
        self.numboxes -= 1
        if self.numboxes >= 1:
            box = self.boxes[-1]
            box['newboxbutton'] = Button(box['frame'], text="Add another >>", command=self.addnewbox)
            box['newboxbutton'].grid(row=1000, column=0, columnspan=100)
            box['deletebutton'] = Button(box['frame'], text="<< Delete", command=self.deletebox)
            box['deletebutton'].grid(row=999, column=0, columnspan=100)
        else:
            self.initializebox()
            self.savebutton.destroy()

    def grab(self):
        pass

#initialize app:
root = Tk()
root.title("WWW Extractor")
root.wm_iconbitmap('py.ico')

app = App(root)

root.mainloop()
