
#include "npc.hpp"

#include <components/esm/loadnpc.hpp>

#include "../mwmechanics/creaturestats.hpp"
#include "../mwmechanics/npcstats.hpp"

#include "../mwworld/ptr.hpp"
#include "../mwworld/actiontalk.hpp"
#include "../mwworld/environment.hpp"
#include "../mwworld/world.hpp"

#include "../mwrender/cellimp.hpp"

#include "../mwmechanics/mechanicsmanager.hpp"
#include <OgreSceneNode.h>

namespace MWClass
{
    std::string Npc::getId (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::NPC, MWWorld::RefData> *ref =
            ptr.get<ESM::NPC>();

        return ref->base->mId;
    }

    void Npc::insertObj (const MWWorld::Ptr& ptr, MWRender::CellRenderImp& cellRender,
        MWWorld::Environment& environment) const
    {
		//Ogre::SceneNode *chest;
        ESMS::LiveCellRef<ESM::NPC, MWWorld::RefData> *ref =
            ptr.get<ESM::NPC>();
		
		//Store scenenodes by npc's name + bodypart [0]  ,  npc's name + bodypart    [1]
		//Ex.                 Fargothchest               ,  Fargothneck

        assert (ref->base != NULL);

		std::string hairID = ref->base->hair;
        std::string headID = ref->base->head;
		std::string npcName = ref->base->name;
		//std::cout << "NPC: " << npcName << "\n";

        //get the part of the bodypart id which describes the race and the gender
        std::string bodyRaceID = headID.substr(0, headID.find_last_of("head_") - 4);
        std::string headModel = "meshes\\" +
            environment.mWorld->getStore().bodyParts.find(headID)->model;

		std::string hairModel = "meshes\\" +
            environment.mWorld->getStore().bodyParts.find(hairID)->model;

        MWRender::Rendering rendering (cellRender, ref->ref);
        

        //TODO: define consts for each bodypart e.g. chest, foot, wrist... and put the parts in the
        // right place
        const ESM::BodyPart *bodyPart =
            environment.mWorld->getStore().bodyParts.search (bodyRaceID + "chest");

		//bodyPart->model->
		Ogre::Vector3 pos = Ogre::Vector3( 20, 20, 20);
		Ogre::Vector3 axis = Ogre::Vector3( 0, 0, 1);
		Ogre::Radian angle = Ogre::Radian(0);
		
		std::string addresses[6] = {"", "", "", "",""};
		std::string addresses2[6] = {"", "", "", "", ""};
		std::string upperleft[5] = {"", "", "", "", ""};
		std::string upperright[5] = {"", "", "", "", ""};
		std::string neckandup[5] = {"", "", "","",""};
		int numbers = 0;
		int uppernumbers = 0;
		int neckNumbers = 0;
		
        if (bodyPart){
			
           cellRender.insertMesh("meshes\\" + bodyPart->model, pos, axis, angle, npcName + "chest", addresses, numbers);
		   addresses2[numbers] = npcName + "chest";
		   addresses[numbers++] = npcName + "chest";
		   upperleft[uppernumbers] = npcName + "chest";
		   upperright[uppernumbers++] = npcName + "chest";
		   neckandup[neckNumbers++] = npcName + "chest";
		}
		   //std::cout << "GETTING NPC PART";
		//Orgre::SceneNode test = cellRender.getNpcPart();

		const ESM::BodyPart *upperleg = environment.mWorld->getStore().bodyParts.search (bodyRaceID + "upper leg");
		const ESM::BodyPart *groin = environment.mWorld->getStore().bodyParts.search (bodyRaceID + "groin");
		const ESM::BodyPart *arm = environment.mWorld->getStore().bodyParts.search (bodyRaceID + "upper arm");
		const ESM::BodyPart *neck = environment.mWorld->getStore().bodyParts.search (bodyRaceID + "neck");
		const ESM::BodyPart *knee = environment.mWorld->getStore().bodyParts.search (bodyRaceID + "knee");
		const ESM::BodyPart *ankle = environment.mWorld->getStore().bodyParts.search (bodyRaceID + "ankle");
		const ESM::BodyPart *foot = environment.mWorld->getStore().bodyParts.search (bodyRaceID + "foot");
		const ESM::BodyPart *foot2 = foot + 1;
		const ESM::BodyPart *wrist = environment.mWorld->getStore().bodyParts.search (bodyRaceID + "wrist");
		const ESM::BodyPart *forearm = environment.mWorld->getStore().bodyParts.search (bodyRaceID + "forearm");
		const ESM::BodyPart *hand = environment.mWorld->getStore().bodyParts.search (bodyRaceID + "hands.1st");


		Ogre::Vector3 pos2 = Ogre::Vector3( 0, .5, 75);
		std::string upperarmpath[2] = {npcName + "chest", npcName + "upper arm"};
		
        if (groin){
            cellRender.insertMesh("meshes\\" + groin->model, pos2, axis, Ogre::Radian(3.14), npcName + "groin", addresses, numbers);
			addresses2[numbers] = npcName + "groin";
			addresses[numbers++] = npcName + "groin";
		}
		
		//addresses[1] = npcName + "groin";
		if(upperleg){
		cellRender.insertMesh ("meshes\\" + upperleg->model, Ogre::Vector3( 6, 0, -14), axis, Ogre::Radian(.7), npcName + "upper leg", addresses, numbers); //-18
		cellRender.insertMesh ("meshes\\" + upperleg->model, Ogre::Vector3( -6, 0, -14), axis, Ogre::Radian(0), npcName + "upper leg2", addresses2, numbers);
		addresses2[numbers] = npcName + "upper leg2";
		addresses[numbers++] = npcName + "upper leg";
		}
		if(knee)
		{
			cellRender.insertMesh ("meshes\\" + knee->model, Ogre::Vector3( 0, -2, -18), axis, Ogre::Radian(0), npcName + "knee", addresses, numbers);
		//cellRender.rotateMesh(Ogre::Vector3(0, 1, 0), Ogre::Radian (1), npcName + "upper arm");
		cellRender.insertMesh ("meshes\\" + knee->model, Ogre::Vector3( 0, -2, -18), axis, Ogre::Radian(0), npcName + "knee2", addresses2, numbers);
		
			addresses2[numbers] = npcName + "knee2";
			addresses[numbers++] = npcName + "knee";
		}
		if(ankle){
			cellRender.insertMesh ("meshes\\" + ankle->model, Ogre::Vector3( 0, 0, -18), axis, Ogre::Radian(0), npcName + "ankle", addresses, numbers);
			cellRender.insertMesh ("meshes\\" + ankle->model, Ogre::Vector3( 0, 0, -18), axis, Ogre::Radian(0), npcName + "ankle2", addresses2, numbers);
			
			addresses2[numbers] = npcName + "ankle2";
			addresses[numbers++] = npcName + "ankle";
		}
		if(foot){
			cellRender.insertMesh ("meshes\\" + foot->model, Ogre::Vector3( 0, -2, -16), axis, Ogre::Radian(3.14), npcName + "foot", addresses, numbers);

			cellRender.insertMesh ("meshes\\" + foot->model, Ogre::Vector3( 0, -2, -16), axis, Ogre::Radian(0), npcName + "foot2", addresses2, numbers);
			addresses2[numbers] = npcName + "foot2";
			addresses[numbers++] = npcName + "foot";
			cellRender.scaleMesh(Ogre::Vector3(1, -1, 1), addresses, numbers);
		}
		
		 
		if (arm){
			cellRender.insertMesh("meshes\\" + arm->model, Ogre::Vector3(-12.5, 0, 104), Ogre::Vector3(1, 0, .75), Ogre::Radian(3.14), npcName + "upper arm", upperleft, uppernumbers);   //1, 0,.75
			 //cellRender.rotateMesh(Ogre::Vector3(1, 0, 0), Ogre::Radian (.45), upperarmpath, 2);                                                                                          //1, 0, 1
			cellRender.insertMesh("meshes\\" + arm->model, Ogre::Vector3(12.5, 0, 105), Ogre::Vector3(-.5, 0, -.75), Ogre::Radian(3.14), npcName + "upper arm2", upperright, uppernumbers);
			upperleft[uppernumbers] = npcName + "upper arm";
			upperright[uppernumbers++] = npcName + "upper arm2";
		}

		if (forearm)
		{
		//addresses[1] = npcName + "upper arm";
			cellRender.insertMesh("meshes\\" + forearm->model, Ogre::Vector3(-12.5, 0, 0), Ogre::Vector3(0, 0, 0), Ogre::Radian(3.14), npcName + "forearm", upperleft, uppernumbers);
			cellRender.insertMesh("meshes\\" + forearm->model, Ogre::Vector3(-12.5, 0, 0), Ogre::Vector3(0, 0, 0), Ogre::Radian(3.14), npcName + "forearm2", upperright, uppernumbers);
			upperleft[uppernumbers] = npcName + "forearm";
			upperright[uppernumbers++] = npcName + "forearm2";
		}
		//else
		//	std::cout << npcName << "has no forearm";
		if (wrist)
		{
			cellRender.insertMesh("meshes\\" + wrist->model, Ogre::Vector3(-9.5, 0, 0), Ogre::Vector3(0, 0, 0), Ogre::Radian(3.14), npcName + "wrist", upperleft, uppernumbers);
			cellRender.insertMesh("meshes\\" + wrist->model, Ogre::Vector3(-9.5, 0, 0), Ogre::Vector3(0, 0, 0), Ogre::Radian(3.14), npcName + "wrist2", upperright, uppernumbers);
			upperleft[uppernumbers] = npcName + "wrist";
			upperright[uppernumbers++] = npcName + "wrist2";
		}
		

		if(hand)
			cellRender.insertMesh("meshes\\" + hand->model, Ogre::Vector3(-50, 0, -120), Ogre::Vector3(0, 0, 0), Ogre::Radian(3.14), npcName + "hands", addresses, 4);   //0, 100, -100    0,0,120
		

		if(neck)
		{
			cellRender.insertMesh ("meshes\\" + neck->model, Ogre::Vector3( 0, 0, 120), axis, Ogre::Radian(3.14), npcName + "neck", neckandup, neckNumbers);
			neckandup[neckNumbers++] = npcName + "neck";
		}
		cellRender.insertMesh (headModel, Ogre::Vector3( 0, 0, 5), axis, Ogre::Radian(0), npcName + "head", neckandup, neckNumbers);
		neckandup[neckNumbers++] = npcName + "head";
		cellRender.insertMesh (hairModel, Ogre::Vector3( 0, -1, 0), axis, Ogre::Radian(0), npcName + "hair", neckandup, neckNumbers);
		ref->mData.setHandle (rendering.end (ref->mData.isEnabled()));
		
	}

    void Npc::enable (const MWWorld::Ptr& ptr, MWWorld::Environment& environment) const
    {
        environment.mMechanicsManager->addActor (ptr);
    }

    void Npc::disable (const MWWorld::Ptr& ptr, MWWorld::Environment& environment) const
    {
        environment.mMechanicsManager->removeActor (ptr);
    }

    std::string Npc::getName (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::NPC, MWWorld::RefData> *ref =
            ptr.get<ESM::NPC>();

        return ref->base->name;
    }

    MWMechanics::CreatureStats& Npc::getCreatureStats (const MWWorld::Ptr& ptr) const
    {
        if (!ptr.getRefData().getCreatureStats().get())
        {
            boost::shared_ptr<MWMechanics::CreatureStats> stats (
                new MWMechanics::CreatureStats);

            ESMS::LiveCellRef<ESM::NPC, MWWorld::RefData> *ref = ptr.get<ESM::NPC>();

            stats->mAttributes[0].set (ref->base->npdt52.strength);
            stats->mAttributes[1].set (ref->base->npdt52.intelligence);
            stats->mAttributes[2].set (ref->base->npdt52.willpower);
            stats->mAttributes[3].set (ref->base->npdt52.agility);
            stats->mAttributes[4].set (ref->base->npdt52.speed);
            stats->mAttributes[5].set (ref->base->npdt52.endurance);
            stats->mAttributes[6].set (ref->base->npdt52.personality);
            stats->mAttributes[7].set (ref->base->npdt52.luck);
            stats->mDynamic[0].set (ref->base->npdt52.health);
            stats->mDynamic[1].set (ref->base->npdt52.mana);
            stats->mDynamic[2].set (ref->base->npdt52.fatigue);

            stats->mLevel = ref->base->npdt52.level;

            ptr.getRefData().getCreatureStats() = stats;
        }

        return *ptr.getRefData().getCreatureStats();
    }

    MWMechanics::NpcStats& Npc::getNpcStats (const MWWorld::Ptr& ptr) const
    {
        if (!ptr.getRefData().getNpcStats().get())
        {
            // xxx
            boost::shared_ptr<MWMechanics::NpcStats> stats (
                new MWMechanics::NpcStats);

            ESMS::LiveCellRef<ESM::NPC, MWWorld::RefData> *ref = ptr.get<ESM::NPC>();

            if (!ref->base->faction.empty())
            {
                // TODO research how initial rank is stored. The information in loadnpc.hpp are at
                // best very unclear.
                stats->mFactionRank[ref->base->faction] = 0;
            }

            for (int i=0; i<27; ++i)
                stats->mSkill[i].setBase (ref->base->npdt52.skills[i]);

            ptr.getRefData().getNpcStats() = stats;
        }

        return *ptr.getRefData().getNpcStats();
    }

    boost::shared_ptr<MWWorld::Action> Npc::activate (const MWWorld::Ptr& ptr,
        const MWWorld::Ptr& actor, const MWWorld::Environment& environment) const
    {
        return boost::shared_ptr<MWWorld::Action> (new MWWorld::ActionTalk (ptr));
    }

    MWWorld::ContainerStore<MWWorld::RefData>& Npc::getContainerStore (const MWWorld::Ptr& ptr)
        const
    {
        if (!ptr.getRefData().getContainerStore().get())
        {
            boost::shared_ptr<MWWorld::ContainerStore<MWWorld::RefData> > store (
                new MWWorld::ContainerStore<MWWorld::RefData>);

            // TODO add initial content

            ptr.getRefData().getContainerStore() = store;
        }

        return *ptr.getRefData().getContainerStore();
    }

    std::string Npc::getScript (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::NPC, MWWorld::RefData> *ref =
            ptr.get<ESM::NPC>();

        return ref->base->script;
    }

    void Npc::registerSelf()
    {
        boost::shared_ptr<Class> instance (new Npc);

        registerClass (typeid (ESM::NPC).name(), instance);
    }
}
