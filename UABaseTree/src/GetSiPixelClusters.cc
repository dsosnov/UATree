//-- Description: Function to retrieve Si cluster rec. hit information

//-- Dataformats
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

#include "Geometry/CommonTopologies/interface/PixelTopology.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"

#include "Geometry/CommonTopologies/interface/StripTopology.h" 
#include "Geometry/TrackerGeometryBuilder/interface/StripGeomDetUnit.h" 
#include "RecoLocalTracker/SiStripClusterizer/interface/SiStripClusterInfo.h"

#include "UATree/UABaseTree/interface/UABaseTree.h"

bool SiPixelClustersDebug = false;

void UABaseTree::GetSiPixelClusters(const edm::Event& event, const edm::EventSetup& setup) {

  outsipixelcluster.clear(); 
 
  edm::ESHandle<TrackerGeometry> trackerGeo;
  setup.get<TrackerDigiGeometryRecord>().get(trackerGeo);

  edm::Handle< edmNew::DetSetVector<SiStripCluster> > stripclusters;
  event.getByLabel(edm::InputTag("siStripClusters"),stripclusters); 

  edm::Handle< edmNew::DetSetVector<SiPixelCluster> > pixelclusters; 
  event.getByLabel(edm::InputTag("siPixelClusters"),pixelclusters);  

  //  outsipixelcluster.assign( pixelclusters->dataSize() + stripclusters->dataSize(), MySiPixelCluster() );  
  outsipixelcluster.assign( pixelclusters->dataSize(), MySiPixelCluster() );


  Int_t j = 0;

  // Loop over entire tracker geometry.
  for (TrackerGeometry::DetContainer::const_iterator i = trackerGeo->dets().begin(); i != trackerGeo->dets().end(); ++i) 
    {
      // See if this is a pixel unit(?).
      if ( GeomDetEnumerators::isTrackerPixel((*i)->subDetector())) 
	{
	  DetId detId = (*i)->geographicalId();

	  // Find all clusters in this module.
	  edmNew::DetSetVector<SiPixelCluster>::const_iterator iSearch = pixelclusters->find(detId);
	  // Loop over all clusters in this module.
	  if (iSearch != pixelclusters->end()) 
	    {
	      for (edmNew::DetSet<SiPixelCluster>::const_iterator clus = iSearch->begin(); clus != iSearch->end(); ++clus) 
		{
		  outsipixelcluster[j].size = clus->size();  
		  outsipixelcluster[j].sizeX = clus->sizeX();  
		  outsipixelcluster[j].sizeY = clus->sizeY();  
		  outsipixelcluster[j].charge = clus->charge();   
		  
		  PixelGeomDetUnit const* theGeomDet = dynamic_cast<PixelGeomDetUnit const*>(trackerGeo->idToDet(detId));
		  PixelTopology const* topol = &(theGeomDet->specificTopology());
		  double x = clus->x();
		  double y = clus->y();
		  LocalPoint clustLP = topol->localPosition(MeasurementPoint(x, y));
		  GlobalPoint clustGP = theGeomDet->surface().toGlobal(clustLP);
		  outsipixelcluster[j].x = clustGP.x();
		  outsipixelcluster[j].y = clustGP.y(); 
                  outsipixelcluster[j].z = clustGP.z();  
		  j++;
		}
	    }
	}

      /*
       * Decided following meeting of Aug 24, 2016 to keep only total # of strip clusters.
       * Code for filling other cluster variables is left commented out here, in case of 
       * need in the future. 
       */
      /*       
      else // If not pixels, strips 
        { 
          DetId detId = (*i)->geographicalId(); 

          // Find all clusters in this module. 
	  edmNew::DetSetVector<SiStripCluster>::const_iterator iSearch = stripclusters->find(detId); 
          // Loop over all clusters in this module. 
          if (iSearch != stripclusters->end())  
            { 
              for (edmNew::DetSet<SiStripCluster>::const_iterator clus = iSearch->begin(); clus != iSearch->end(); ++clus)  
                { 
		  outsicluster[j].firstStrip = clus->firstStrip(); 
		  outsicluster[j].barycenter = clus->barycenter(); 
		  outsicluster[j].charge = clus->charge();   

		  SiStripClusterInfo* siStripClusterInfo = new SiStripClusterInfo(*clus,setup,detId,std::string("")); //string = quality label
		  float clPosition = siStripClusterInfo->baryStrip();
		  const StripGeomDetUnit* sgdu = static_cast<const StripGeomDetUnit*>(trackerGeo->idToDet(detId));
		  Surface::GlobalPoint clustGP = sgdu->surface().toGlobal(sgdu->specificTopology().localPosition(MeasurementPoint(clPosition,0)));

                  outsicluster[j].x = clustGP.x(); 
                  outsicluster[j].y = clustGP.y();  
                  outsicluster[j].z = clustGP.z();   

		  j++;
		}
	    }
	}
	*/

    }
}
