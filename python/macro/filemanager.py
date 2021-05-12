import ROOT
import csv

def GetKeyNames( self , dir = ''):
    self.cd(dir)
    return [key.GetName() for key in ROOT.gDirectory.GetListOfKeys()]

class filemanager:
    filedictofdict = {}
    def __init__(self,filename):
        self.treedict = {}
        self.treenametobranchdict = {}
        self.subfile = []
        self.subfilename = []
        self.l = []
        self.hasevent = []
        filehead = filename.replace(".root",'')
        filecsv = filehead + ".csv"
        fi = open(filecsv)
        reader = csv.reader(fi)
        l = [row for row in reader]
        for l0 in l[0]:
            self.subfilename.append(l0)
            subfileroot = l0.replace(".csv",'') + ".root"
            self.subfile.append(filemanager(subfileroot))
        self.filename = filename
        self.f = ROOT.TFile(filename)
        treename = self.f.GetKeyNames()
        for name in treename:
            self.treedict[name] = self.f.Get(name)
            branchdictin = {}
            self.treedict[name].GetEntry(0)
            brlist = self.treedict[name].GetListOfBranches()
            nbr = brlist.GetEntries()
            itr = brlist.MakeIterator()
            for i in range(nbr):
                bname = itr().GetName()
                back = 'branchdictin[bname] = self.treedict[name].'
                exec(back + bname)
                if bname == "wcsimrootevent":
                    self.treedict[name].GetBranch(bname).SetAutoDelete()
            self.treenametobranchdict[name] = branchdictin
        
    def GetValue(self,valuename,event):
        value = [0.,"true"]
        try:
            valuesplit = valuename.split('.')
            treename = valuesplit[0]
            branchname = valuesplit[1]
            valueremovebranchname = valuename.replace(treename + '.' + branchname,'')
            exevalue = ""
            self.treedict[treename].GetEntry(event)
            exevalue = 'self.treenametobranchdict["' + treename + '"]["' + branchname + '"]' +  valueremovebranchname
            value[0] = (eval(exevalue))
            value[1] = "true"
            return value
        except:
            for sub in self.subfile:
                return sub.GetValue(valuename,event)
            value[1] = "false"
            return value
    def GetNeventmax(self):
        value = 0
        for t in self.treedict.values():
            if value < t.GetEntries():
                value = t.GetEntries()
        return value
        
