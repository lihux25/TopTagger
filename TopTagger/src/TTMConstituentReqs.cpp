#include "TopTagger/TopTagger/include/TTMConstituentReqs.h"

#include "TopTagger/TopTagger/include/Constituent.h"
#include "TopTagger/CfgParser/include/Context.hh"
#include "TopTagger/CfgParser/include/CfgDocument.hh"

void TTMConstituentReqs::getParameters(const cfg::CfgDocument* cfgDoc, const std::string& localContextName)
{
    //Construct contexts
    cfg::Context commonCxt("Common");
    cfg::Context localCxt(localContextName);
    
    //monojet parameters
    minAK8TopMass_    = cfgDoc->get("minAK8TopMass",    localCxt, -999.9);
    maxAK8TopMass_    = cfgDoc->get("maxAK8TopMass",    localCxt, -999.9);
    maxTopTau32_      = cfgDoc->get("maxTopTau32",      localCxt, -999.9);
    minAK8TopPt_      = cfgDoc->get("minAK8TopPt",      localCxt, -999.9);

    //dijet parameters
    minAK8WMass_      = cfgDoc->get("minAK8WMass",      localCxt, -999.9);
    maxAK8WMass_      = cfgDoc->get("maxAK8WMass",      localCxt, -999.9);
    maxWTau21_        = cfgDoc->get("maxWTau21",        localCxt, -999.9);
    minAK8WPt_        = cfgDoc->get("minAK8WPt",        localCxt, -999.9);
    minAK4WPt_        = cfgDoc->get("minAK4WPt",        localCxt, -999.9);

    //trijet parameters
    minAK4ResolvedPt_ = cfgDoc->get("minAK4ResolvedPt", localCxt, -999.9);
}

bool TTMConstituentReqs::passAK8WReqs(const Constituent& constituent) const
{
    //check that it is an AK8 jet
    if(constituent.getType() != AK8JET) return false;

    //check that tau1 and 2 are valid
    if(constituent.getTau1() <= 0 || constituent.getTau2() <= 0) return false;

    double tau21 = constituent.getTau2()/constituent.getTau1();

    return constituent.p().Pt() > minAK8WPt_ &&
           constituent.getSoftDropMass() > minAK8WMass_  && 
           constituent.getSoftDropMass() < maxAK8WMass_ &&
           tau21 < maxWTau21_;
}

bool TTMConstituentReqs::passAK4WReqs(const Constituent& constituent) const
{
    return constituent.getType() == AK4JET && constituent.p().Pt() > minAK4WPt_;
}

bool TTMConstituentReqs::passAK8TopReqs(const Constituent& constituent) const
{
    //check that it is an AK8 jet
    if(constituent.getType() != AK8JET) return false;

    //check that tau2 and 3 are valid
    if(constituent.getTau2() <= 0 || constituent.getTau3() <= 0) return false;

    double tau32 = constituent.getTau3()/constituent.getTau2();

    return constituent.p().Pt() > minAK8TopPt_ &&
           constituent.getSoftDropMass() > minAK8TopMass_  && 
           constituent.getSoftDropMass() < maxAK8TopMass_ &&
           tau32 < maxTopTau32_;
}

bool TTMConstituentReqs::passAK4ResolvedReqs(const Constituent& constituent) const
{
    return constituent.getType() == AK4JET && constituent.p().Pt() > minAK4ResolvedPt_;
}
