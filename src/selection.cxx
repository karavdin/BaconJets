#include "UHH2/BaconJets/include/selection.h"

#include "UHH2/BaconTrans/baconheaders/TJet.hh"
#include "UHH2/BaconTrans/baconheaders/TVertex.hh"
#include "UHH2/BaconJets/include/constants.h"

#include "TVector2.h"

namespace uhh2bacon {

Selection::Selection(uhh2::Context & ctx) :
    context(ctx),
    event(0)
{
  auto jetCollection = ctx.get("jetCollection");
  h_jets = ctx.declare_event_input<TClonesArray>(jetCollection);
  //    h_jets = context.declare_event_input<TClonesArray>("AK4PFCHS");
  // h_jets = context.declare_event_input<TClonesArray>("AK4PFPUPPI");
  h_eventInfo = context.declare_event_input<baconhep::TEventInfo>("Info");
  h_pv = context.declare_event_input<TClonesArray>("PV");

  tt_gen_pthat = ctx.declare_event_output<float>("gen_pthat");
  tt_gen_weight = ctx.declare_event_output<float>("gen_weight");
  tt_jet1_pt = ctx.declare_event_output<float>("jet1_pt");
  tt_jet2_pt = ctx.declare_event_output<float>("jet2_pt");
  tt_jet3_pt = ctx.declare_event_output<float>("jet3_pt");
  tt_jet1_ptRaw = ctx.declare_event_output<float>("jet1_ptRaw");
  tt_jet2_ptRaw = ctx.declare_event_output<float>("jet2_ptRaw");
  tt_jet3_ptRaw = ctx.declare_event_output<float>("jet3_ptRaw");
  tt_nvertices = ctx.declare_event_output<int>("nvertices");
  //  tt_nGoodvertices = ctx.declare_event_output<int>("nGoodvertices");
  tt_probejet_eta = ctx.declare_event_output<float>("probejet_eta");
  tt_probejet_phi = ctx.declare_event_output<float>("probejet_phi");
  tt_probejet_pt = ctx.declare_event_output<float>("probejet_pt");
  tt_probejet_ptRaw = ctx.declare_event_output<float>("probejet_ptRaw");
  tt_barreljet_eta = ctx.declare_event_output<float>("barreljet_eta");
  tt_barreljet_phi = ctx.declare_event_output<float>("barreljet_phi");
  tt_barreljet_pt = ctx.declare_event_output<float>("barreljet_pt");
  tt_barreljet_ptRaw = ctx.declare_event_output<float>("barreljet_ptRaw");
  tt_pt_ave = ctx.declare_event_output<float>("pt_ave");
  tt_alpha = ctx.declare_event_output<float>("alpha");
  tt_rel_r = ctx.declare_event_output<float>("rel_r");
  tt_mpf_r = ctx.declare_event_output<float>("mpf_r");
  tt_asymmetry = ctx.declare_event_output<float>("asymmetry");
  tt_nPU = ctx.declare_event_output<int>("nPU");

}

void Selection::SetEvent(uhh2::Event& evt)
{
   event = &evt;
   assert(event);
}

bool Selection::PtMC(uhh2::Event& evt)
{
  assert(event);
  //  std::cout<<"evt.get(tt_pt_ave) = "<<evt.get(tt_pt_ave)<<" s_Pt_Ave40_cut = "<<s_Pt_Ave40_cut<<std::endl;
  if (evt.get(tt_pt_ave) < s_Pt_Ave40_cut) 
    return false;
  return true;
}

bool Selection::Trigger(uhh2::Event& evt)
{
    assert(event);

    const baconhep::TEventInfo & info = event->get(h_eventInfo);
//   const baconhep::TJet * jet = dynamic_cast<const baconhep::TJet*>(js[0]);
//   assert(jet);

    baconhep::TEventInfo* eventInfo= new baconhep::TEventInfo(info);
    assert(eventInfo);

    /*
    ///triggerNames  briggerBits
    //nominal triggers
    bool trigger40fired = false;
    bool trigger60fired = false;
    //    bool trigger80fired = false;
    //    bool trigger140fired = false;
    bool trigger200fired = false;
    bool trigger260fired = false;
    bool trigger320fired = false;
    bool trigger400fired = false;
    bool trigger500fired = false;
//     Triggers Bits:
//     HLT_DiPFJetAve140 = triggerBits[1]
//     HLT_DiPFJetAve200 = triggerBits[3]
//     HLT_DiPFJetAve260 = triggerBits[5]
//     HLT_DiPFJetAve320 = triggerBits[7]
//     HLT_DiPFJetAve40  = triggerBits[9]
//     HLT_DiPFJetAve400 = triggerBits[8]
//     HLT_DiPFJetAve500 = triggerBits[10]
//     HLT_DiPFJetAve60  = triggerBits[12]
//     HLT_DiPFJetAve80  = triggerBits[14]


    if(eventInfo->triggerBits[9]==1)  trigger40fired = true;
    if(eventInfo->triggerBits[12]==1) trigger60fired = true;
    //    if(eventInfo->triggerBits[14]==1) trigger80fired = true;
    //    if(eventInfo->triggerBits[1]==1)  trigger140fired = true;
    if(eventInfo->triggerBits[3]==1)  trigger200fired = true;
    if(eventInfo->triggerBits[5]==1)  trigger260fired = true;
    if(eventInfo->triggerBits[7]==1)  trigger320fired = true;
    if(eventInfo->triggerBits[8]==1)  trigger400fired = true;
    if(eventInfo->triggerBits[10]==1) trigger500fired = true;

    //    std::cout<<"evt.get(tt_pt_ave) = "<<evt.get(tt_pt_ave)<<" s_Pt_Ave40_cut = "<<s_Pt_Ave40_cut<<std::endl;
    if (evt.get(tt_pt_ave) < s_Pt_Ave40_cut) return false;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave40_cut  && evt.get(tt_pt_ave) < s_Pt_Ave60_cut  && trigger40fired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave60_cut  && evt.get(tt_pt_ave) < s_Pt_Ave80_cut  && trigger60fired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave80_cut  && evt.get(tt_pt_ave) < s_Pt_Ave140_cut && trigger60fired) return true; //change back to trigger80fired (RunII2015 L1 is less efficient!)
    if (evt.get(tt_pt_ave) >= s_Pt_Ave140_cut && evt.get(tt_pt_ave) < s_Pt_Ave200_cut && trigger60fired) return true; //change back to trigger140fired (RunII2015 L1 is less efficient!)
    if (evt.get(tt_pt_ave) >= s_Pt_Ave200_cut && evt.get(tt_pt_ave) < s_Pt_Ave260_cut && trigger200fired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave260_cut && evt.get(tt_pt_ave) < s_Pt_Ave320_cut && trigger260fired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave320_cut && evt.get(tt_pt_ave) < s_Pt_Ave400_cut && trigger320fired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave400_cut && evt.get(tt_pt_ave) < s_Pt_Ave500_cut && trigger400fired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave500_cut && trigger500fired) return true;
    */

    /*
//     for HF triggers

    bool trigger60HFfired = false;
    bool trigger80HFfired = false;
    bool trigger100HFfired = false;
    bool trigger160HFfired = false;
    bool trigger220HFfired = false;
    bool trigger300HFfired = false;
//     Triggers Bits:
//     HLT_DiPFJetAve100_HFJEC = triggerBits[0]
//     HLT_DiPFJetAve160_HFJEC = triggerBits[2]
//     HLT_DiPFJetAve220_HFJEC = triggerBits[4]
//     HLT_DiPFJetAve300_HFJEC = triggerBits[6]
//     HLT_DiPFJetAve60_HFJEC = triggerBits[11]
//     HLT_DiPFJetAve80_HFJEC = triggerBits[13]


    if(eventInfo->triggerBits[11]==1) trigger60HFfired = true;
    if(eventInfo->triggerBits[13]==1) trigger80HFfired = true;
    if(eventInfo->triggerBits[0]==1)  trigger100HFfired = true;
    if(eventInfo->triggerBits[2]==1)  trigger160HFfired = true;
    if(eventInfo->triggerBits[4]==1)  trigger220HFfired = true;
    if(eventInfo->triggerBits[6]==1)  trigger300HFfired = true;


    if (evt.get(tt_pt_ave) < s_Pt_Ave60HF_cut) return false;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave60HF_cut  && evt.get(tt_pt_ave) < s_Pt_Ave80HF_cut  && trigger60HFfired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave80HF_cut  && evt.get(tt_pt_ave) < s_Pt_Ave100HF_cut && trigger80HFfired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave100HF_cut && evt.get(tt_pt_ave) < s_Pt_Ave160HF_cut && trigger100HFfired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave160HF_cut && evt.get(tt_pt_ave) < s_Pt_Ave220HF_cut && trigger160HFfired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave220HF_cut && evt.get(tt_pt_ave) < s_Pt_Ave300HF_cut && trigger220HFfired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave300HF_cut && trigger300HFfired) return true;
    */

//     //For combination of triggers
 //nominal triggers
    bool trigger40fired = false;
    bool trigger60fired = false;
    bool trigger80fired = false;
    bool trigger140fired = false;
    bool trigger200fired = false;
    bool trigger260fired = false;
    bool trigger320fired = false;
    bool trigger400fired = false;
    bool trigger500fired = false;
//     Triggers Bits:
//     HLT_DiPFJetAve140 = triggerBits[1]
//     HLT_DiPFJetAve200 = triggerBits[3]
//     HLT_DiPFJetAve260 = triggerBits[5]
//     HLT_DiPFJetAve320 = triggerBits[7]
//     HLT_DiPFJetAve40  = triggerBits[9]
//     HLT_DiPFJetAve400 = triggerBits[8]
//     HLT_DiPFJetAve500 = triggerBits[10]
//     HLT_DiPFJetAve60  = triggerBits[12]
//     HLT_DiPFJetAve80  = triggerBits[14]


    if(eventInfo->triggerBits[9]==1)  trigger40fired = true;
    if(eventInfo->triggerBits[12]==1) trigger60fired = true;
    if(eventInfo->triggerBits[14]==1) trigger80fired = true;
    if(eventInfo->triggerBits[1]==1)  trigger140fired = true;
    if(eventInfo->triggerBits[3]==1)  trigger200fired = true;
    if(eventInfo->triggerBits[5]==1)  trigger260fired = true;
    if(eventInfo->triggerBits[7]==1)  trigger320fired = true;
    if(eventInfo->triggerBits[8]==1)  trigger400fired = true;
    if(eventInfo->triggerBits[10]==1) trigger500fired = true;

    //    std::cout<<"evt.get(tt_pt_ave) = "<<evt.get(tt_pt_ave)<<" s_Pt_Ave40_cut = "<<s_Pt_Ave40_cut<<std::endl;
    if (evt.get(tt_pt_ave) < s_Pt_Ave40_cut) return false;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave40_cut  && evt.get(tt_pt_ave) < s_Pt_Ave60_cut  && trigger40fired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave60_cut  && evt.get(tt_pt_ave) < s_Pt_Ave80_cut  && trigger60fired) return true;
    //    if (evt.get(tt_pt_ave) >= s_Pt_Ave80_cut  && evt.get(tt_pt_ave) < s_Pt_Ave140_cut && trigger60fired) return true; //change back to trigger80fired (RunII2015 L1 is less efficient!)
    //    if (evt.get(tt_pt_ave) >= s_Pt_Ave140_cut && evt.get(tt_pt_ave) < s_Pt_Ave200_cut && trigger60fired) return true; //change back to trigger140fired (RunII2015 L1 is less efficient!)
    if (evt.get(tt_pt_ave) >= s_Pt_Ave80_cut  && evt.get(tt_pt_ave) < s_Pt_Ave140_cut && trigger80fired) return true; //change back to trigger80fired (RunII2015 L1 is less efficient!)
    if (evt.get(tt_pt_ave) >= s_Pt_Ave140_cut && evt.get(tt_pt_ave) < s_Pt_Ave200_cut && trigger140fired) return true; //change back to trigger140fired (RunII2015 L1 is less efficient!)
    if (evt.get(tt_pt_ave) >= s_Pt_Ave200_cut && evt.get(tt_pt_ave) < s_Pt_Ave260_cut && trigger200fired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave260_cut && evt.get(tt_pt_ave) < s_Pt_Ave320_cut && trigger260fired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave320_cut && evt.get(tt_pt_ave) < s_Pt_Ave400_cut && trigger320fired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave400_cut && evt.get(tt_pt_ave) < s_Pt_Ave500_cut && trigger400fired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave500_cut && trigger500fired) return true;

    // //HF triggers -------------------------------------------------------------------------------------------
    bool trigger60HFfired = false;
    bool trigger80HFfired = false;
    bool trigger100HFfired = false;
    bool trigger160HFfired = false;
    bool trigger220HFfired = false;
    bool trigger300HFfired = false;
    //     Triggers Bits:
    //     HLT_DiPFJetAve100_HFJEC = triggerBits[0]
    //     HLT_DiPFJetAve160_HFJEC = triggerBits[2]
    //     HLT_DiPFJetAve220_HFJEC = triggerBits[4]
    //     HLT_DiPFJetAve300_HFJEC = triggerBits[6]
    //     HLT_DiPFJetAve60_HFJEC = triggerBits[11]
    //     HLT_DiPFJetAve80_HFJEC = triggerBits[13]
    
    if(eventInfo->triggerBits[11]==1) trigger60HFfired = true;
    if(eventInfo->triggerBits[13]==1) trigger80HFfired = true;
    if(eventInfo->triggerBits[0]==1)  trigger100HFfired = true;
    if(eventInfo->triggerBits[2]==1)  trigger160HFfired = true;
    if(eventInfo->triggerBits[4]==1)  trigger220HFfired = true;
    if(eventInfo->triggerBits[6]==1)  trigger300HFfired = true;


    if (evt.get(tt_pt_ave) < s_Pt_Ave60HF_cut) return false;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave60HF_cut  && evt.get(tt_pt_ave) < s_Pt_Ave80HF_cut  && trigger60HFfired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave80HF_cut  && evt.get(tt_pt_ave) < s_Pt_Ave100HF_cut && trigger80HFfired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave100HF_cut && evt.get(tt_pt_ave) < s_Pt_Ave160HF_cut && trigger100HFfired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave160HF_cut && evt.get(tt_pt_ave) < s_Pt_Ave220HF_cut && trigger160HFfired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave220HF_cut && evt.get(tt_pt_ave) < s_Pt_Ave300HF_cut && trigger220HFfired) return true;
    if (evt.get(tt_pt_ave) >= s_Pt_Ave300HF_cut && trigger300HFfired) return true;
    //---------------------------------------------------------------------------------------------------




 return false;
}

bool Selection::DiJet()
{
    assert(event);

    const TClonesArray & js = event->get(h_jets);
    const baconhep::TEventInfo & info = event->get(h_eventInfo);
    baconhep::TEventInfo* eventInfo= new baconhep::TEventInfo(info);
    assert(eventInfo);

    int njets = js.GetEntries();
//     std::cout << "hallo"<<std::endl;

    // njets >= 2
    if (njets>=2) return true;

 return false;
}
bool Selection::DiJetAdvanced(uhh2::Event& evt)
{
    assert(event);

    const TClonesArray & js = event->get(h_jets);
    const baconhep::TEventInfo & info = event->get(h_eventInfo);
//   const baconhep::TJet * jet = dynamic_cast<const baconhep::TJet*>(js[0]);
//   assert(jet);

    baconhep::TEventInfo* eventInfo= new baconhep::TEventInfo(info);
    assert(eventInfo);
//   const baconhep::TJet * jet = dynamic_cast<const baconhep::TJet*>(js[0]);
//   assert(jet);

    int njets = js.GetEntries();

     // njets >= 2
    if (njets < 2) return false;

    baconhep::TJet* jet1 = (baconhep::TJet*)js[0];
    baconhep::TJet* jet2 = (baconhep::TJet*)js[1];

    // at least one barrel jet
    if((fabs(jet1->eta) >= s_eta_barr) && (fabs(jet2->eta) >= s_eta_barr)) return false; 

    // delta phi < 2.7
    double deltaPhi = std::abs(TVector2::Phi_mpi_pi(jet1->phi - jet2->phi));
    if (deltaPhi < s_delta_phi) return false;

    // |asymm| < 0.7
    if (fabs((evt.get(tt_jet2_pt) - evt.get(tt_jet1_pt)) / (evt.get(tt_jet2_pt) + evt.get(tt_jet1_pt))) > s_asymm) return false;

    // p_t,rel < 0.2
//     if (njets>2){
//         baconhep::TJet* jet3 = (baconhep::TJet*)js[2];
//         if ((2*(evt.jet3_pt))/(evt.jet1_pt + evt.jet2_pt) > s_pt_rel) return false;
//     }

    return true;
}

  ///  bool Selection::goodPVertex(int goodVtx = 0)
  int Selection::goodPVertex()
{
    assert(event);
    //    event->set(tt_nGoodvertices,0); //set default value  
    const TClonesArray & pvs = event->get(h_pv);

    Int_t nvertices = pvs.GetEntries();
    // require in the event that there is at least one reconstructed vertex
    if(nvertices<=0) return 0;//false;
    float nPrVer = 0;
    // pick the first (i.e. highest sum pt) verte
    for (int i=0; i<nvertices; i++){
        baconhep::TVertex* vertices = (baconhep::TVertex*)pvs[i];
        // require that the vertex meets certain criteria
	//	if(vertices->nTracksFit)
	//	std::cout<<" vertices->nTracksFit = "<<vertices->nTracksFit<<" "<<fabs(vertices->z)<<" cut at "<<s_n_PvTracks<<std::endl;
	//        if((vertices->nTracksFit > s_n_PvTracks) && (fabs(vertices->z) < s_n_Pv_z) && (fabs(vertices->y) < s_n_Pv_xy) && (fabs(vertices->x) < s_n_Pv_xy)){
	//SHOULD BE LIKE
	//cms.string("isValid & ndof >= 4 & chi2 > 0 & tracksSize > 0 & abs(z) < 24 & abs(position.Rho) < 2.")
        if((fabs(vertices->z) < 24.) && (fabs(vertices->rho) < 2.) && (vertices->ndof >= 4) 
	   && (vertices->chi2) > 0 && (vertices->isValid)){
            nPrVer++;
        }
    }
    return nPrVer;
    //    std::cout<<" nPrVer = "<<nPrVer<<" all vtxs = "<<nvertices<<std::endl;
    //    event->set(tt_nGoodvertices,nPrVer); 
    // goodVtx = nPrVer; 
    // if(nPrVer<=0) return false;
    // else
    //   return true;
}





bool Selection::FullSelection()
{
  bool goodVtx = false;
  if(goodPVertex()>0) goodVtx = true; 
  //  return DiJet()&&goodPVertex();
  return DiJet()&& goodVtx;

}

Selection::~Selection()
{
}

}
