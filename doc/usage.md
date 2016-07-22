Using FCC-EDM collections
==

This document describes some typical use-cases. A [corresponding document](https://github.com/HEP-FCC/podio/blob/master/doc/examples.md) for general usage of PODIO has some additional information.

Object Ownership
--

Every data object created and added to a collection is owned by the collection and garbage collected at the end of event processing.

Object creation
--

Each collection allows the creation of objects with the factory method `create`, using this ensures correct object ownership and is recommended. More details in the [PODIO examples](https://github.com/HEP-FCC/podio/blob/master/doc/examples.md).


Data composition
--

In the [design](./design.md) document we already mentioned that an influencing factor was to ease writing re-usable code. This lead to the introduction of the `Core` PODs you defined at the very top of the [edm.yaml](https://github.com/HEP-FCC/fcc-edm/blob/master/edm.yaml). For example both `fcc::Particle` and `fcc::MCParticle` have the member `fcc::BareParticle`:

~~~{.cpp}
void setKinematics(fcc::BareParticle& p, double pt, double eta, double phi) {
    p.P4.Px = TMath::Cos(phi)*pt;
    p.P4.Py = TMath::Sin(phi)*pt;
    p.P4.Pz = TMath::Sinh(eta)*pt;
}

// First get the collection (note that this will work differently in FCCSW, see below)
auto& myParticleColl = store.create<fcc::ParticleCollection>("recoParticles");
auto& myMCParticleCollection = store.create<fcc::MCParticleCollection>("genParticles");
auto particle = myParticleCollection.create();
auto mcParticle = myMCParticleCollection.create();

setKinematics(particle.Core, 20, 0.1, 0.5);
setKinematics(mcParticle.Core, 20, 0.1, 0.5);
~~~

Utilities
--
We provide a number of uitility functions that may be commonly needed when working with the FCC-EDM.

### Traversing particle histories
