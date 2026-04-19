"use client"

import { useState } from "react"
import { use } from "react"
import { Phone, Calendar, MapPin, Clock, Star, ExternalLink, Building2, Pill, Stethoscope, Users, Award, Shield } from "lucide-react"
import { Button } from "@/components/ui/button"
import { MedicineCard, type Medicine } from "@/components/pharmacy/medicine-card"
import Link from "next/link"
import { cn } from "@/lib/utils"

interface HealthInstitution {
  id: string
  name: string
  type: "farmacia" | "hospital" | "posto"
  address: string
  rating: number
  reviews: string
  status: string
  phone: string
  hours: string
  services: string[]
  description: string
  image: string
  specialties?: string[]
  beds?: number
  doctors?: number
}

const institutionData: Record<string, HealthInstitution> = {
  welwitschia: {
    id: "welwitschia",
    name: "Farmacia Welwitschia",
    type: "farmacia",
    address: "Talatona, Rua do MAT, Luanda",
    rating: 4.8,
    reviews: "120+",
    status: "Aberto 24h",
    phone: "+244 923 000 001",
    hours: "Seg - Dom: 24 Horas",
    services: ["Medicamentos", "Testes Rapidos", "Cosmeticos", "Suplementos"],
    description: "Uma das maiores farmacias de Talatona, oferecendo uma vasta gama de medicamentos e produtos de saude.",
    image: "https://images.unsplash.com/photo-1586015555751-63bb77f4322a?w=1200&h=600&fit=crop",
  },
  maianga: {
    id: "maianga",
    name: "Apothecary Maianga",
    type: "farmacia",
    address: "Maianga, Av. Revolucao de Outubro, Luanda",
    rating: 4.9,
    reviews: "340+",
    status: "Aberto 24h",
    phone: "+244 923 000 002",
    hours: "Seg - Dom: 24 Horas",
    services: ["Medicamentos", "Vacinacao", "Testes COVID", "Produtos Naturais"],
    description: "Farmacia moderna com servico de vacinacao e testes rapidos. Atendimento 24 horas.",
    image: "https://images.unsplash.com/photo-1631549916768-4119b2e5f926?w=1200&h=600&fit=crop",
  },
  "hospital-militar": {
    id: "hospital-militar",
    name: "Hospital Militar Principal",
    type: "hospital",
    address: "Maianga, Luanda",
    rating: 4.6,
    reviews: "890+",
    status: "Aberto 24h",
    phone: "+244 222 000 000",
    hours: "Seg - Dom: 24 Horas",
    services: ["Urgencias", "Cirurgia", "Internamento", "Consultas", "Laboratorio"],
    description: "Hospital de referencia em Angola, oferecendo cuidados de saude de alta qualidade com equipamentos modernos.",
    image: "https://images.unsplash.com/photo-1519494026892-80bbd2d6fd0d?w=1200&h=600&fit=crop",
    specialties: ["Cardiologia", "Ortopedia", "Neurologia", "Pediatria", "Ginecologia"],
    beds: 450,
    doctors: 120,
  },
  "centro-saude-cazenga": {
    id: "centro-saude-cazenga",
    name: "Centro de Saude do Cazenga",
    type: "posto",
    address: "Cazenga, Rua Principal, Luanda",
    rating: 4.3,
    reviews: "156",
    status: "Aberto",
    phone: "+244 923 111 222",
    hours: "Seg - Sex: 07:00 - 19:00",
    services: ["Consultas Gerais", "Vacinacao", "Saude Materna", "Pediatria"],
    description: "Centro de saude comunitario oferecendo cuidados primarios de saude para a populacao do Cazenga.",
    image: "https://images.unsplash.com/photo-1538108149393-fbbd81895907?w=1200&h=600&fit=crop",
    doctors: 8,
  },
  "clinica-sagrada": {
    id: "clinica-sagrada",
    name: "Clinica Sagrada Esperanca",
    type: "hospital",
    address: "Talatona, Zona Economica Especial, Luanda",
    rating: 4.9,
    reviews: "1.2k",
    status: "Aberto 24h",
    phone: "+244 226 430 000",
    hours: "Seg - Dom: 24 Horas",
    services: ["Urgencias", "Cirurgia Avancada", "Internamento VIP", "Maternidade", "Imagiologia"],
    description: "Clinica privada de referencia em Angola, com tecnologia de ponta e profissionais altamente qualificados.",
    image: "https://images.unsplash.com/photo-1587351021759-3e566b6af7cc?w=1200&h=600&fit=crop",
    specialties: ["Cardiologia", "Oncologia", "Transplantes", "Medicina Nuclear", "Neurocirurgia"],
    beds: 300,
    doctors: 180,
  },
  "farmacia-central": {
    id: "farmacia-central",
    name: "Farmacia Central",
    type: "farmacia",
    address: "Ingombota, Rua Rainha Ginga, Luanda",
    rating: 4.5,
    reviews: "89",
    status: "Fecha em 1h",
    phone: "+244 923 000 003",
    hours: "Seg - Sab: 08:00 - 20:00",
    services: ["Medicamentos", "Produtos de Higiene", "Equipamentos Medicos"],
    description: "Farmacia tradicional no coracao de Luanda, servindo a comunidade ha mais de 30 anos.",
    image: "https://images.unsplash.com/photo-1576602976047-174e57a47881?w=1200&h=600&fit=crop",
  },
  "posto-viana": {
    id: "posto-viana",
    name: "Posto Medico de Viana",
    type: "posto",
    address: "Viana, Sector 12, Luanda",
    rating: 4.2,
    reviews: "67",
    status: "Aberto",
    phone: "+244 923 333 444",
    hours: "Seg - Sex: 08:00 - 17:00",
    services: ["Consultas", "Vacinacao", "Curativos", "Planeamento Familiar"],
    description: "Posto medico comunitario atendendo as necessidades basicas de saude da populacao de Viana.",
    image: "https://images.unsplash.com/photo-1504439468489-c8920d796a29?w=1200&h=600&fit=crop",
    doctors: 4,
  },
}

const medicines: Medicine[] = [
  {
    id: "paracetamol",
    name: "Paracetamol 500mg",
    description: "Caixa de 20 comprimidos",
    price: 1250,
    image: "https://images.unsplash.com/photo-1584308666744-24d5c474f2ae?w=200&h=200&fit=crop",
    inStock: true,
  },
  {
    id: "vitamina-c",
    name: "Vitamina C 1g",
    description: "Tubo 10 pastilhas eferv.",
    price: 2400,
    image: "https://images.unsplash.com/photo-1550572017-4fcdbb59cc32?w=200&h=200&fit=crop",
    inStock: true,
  },
  {
    id: "amoxicilina",
    name: "Amoxicilina 500mg",
    description: "Requer Receita Medica",
    price: 3800,
    image: "https://images.unsplash.com/photo-1471864190281-a93a3070b6de?w=200&h=200&fit=crop",
    inStock: true,
    requiresPrescription: true,
  },
  {
    id: "ibuprofeno",
    name: "Ibuprofeno 400mg",
    description: "Caixa de 12 comprimidos",
    price: 1800,
    image: "https://images.unsplash.com/photo-1550572017-edd951aa8f72?w=200&h=200&fit=crop",
    inStock: true,
  },
]

const typeConfig = {
  farmacia: { 
    label: "Farmacia", 
    icon: Pill, 
    color: "text-blue-600" 
  },
  hospital: { 
    label: "Hospital", 
    icon: Building2, 
    color: "text-red-600" 
  },
  posto: { 
    label: "Posto Medico", 
    icon: Stethoscope, 
    color: "text-green-600" 
  },
}

export default function InstitutionDetailsPage({ params }: { params: Promise<{ id: string }> }) {
  const resolvedParams = use(params)
  const [activeFilter, setActiveFilter] = useState("Todos")
  
  const institution = institutionData[resolvedParams.id] || institutionData.maianga
  const typeInfo = typeConfig[institution.type]
  const TypeIcon = typeInfo.icon

  const filterTabs = institution.type === "farmacia" 
    ? ["Todos", "Dor", "Antibioticos", "Vitaminas"]
    : ["Todos", "Consultas", "Urgencias", "Especialidades"]

  return (
    <div className="pb-8">
      {/* Hero Section */}
      <section className="relative h-[400px] w-full overflow-hidden -mt-8">
        <img
          src={institution.image}
          alt={institution.name}
          className="w-full h-full object-cover"
        />
        <div className="absolute inset-0 bg-gradient-to-t from-black/70 to-transparent" />
        
        <div className="absolute bottom-0 left-0 p-8 w-full">
          <div className="max-w-6xl mx-auto flex flex-col md:flex-row md:items-end justify-between gap-6">
            <div>
              <div className="flex items-center gap-2 mb-3">
                <span className={cn("flex items-center gap-1 text-[10px] font-bold px-3 py-1 rounded-full uppercase tracking-widest bg-white/20 backdrop-blur-md text-white")}>
                  <TypeIcon className="w-3 h-3" />
                  {typeInfo.label}
                </span>
                <span className="bg-tertiary-fixed text-on-tertiary-fixed text-[10px] font-bold px-3 py-1 rounded-full uppercase tracking-widest">
                  {institution.status}
                </span>
                <div className="flex items-center gap-1 text-white text-sm bg-black/20 backdrop-blur-md px-3 py-1 rounded-full">
                  <Star className="w-4 h-4 fill-current" />
                  {institution.rating} ({institution.reviews} avaliacoes)
                </div>
              </div>
              <h1 className="text-4xl md:text-5xl font-extrabold text-white mb-2 font-serif">
                {institution.name}
              </h1>
              <p className="text-white/80 flex items-center gap-2">
                <MapPin className="w-4 h-4" />
                {institution.address}
              </p>
            </div>
            
            <div className="flex gap-4">
              <Button size="lg" className="px-8 rounded-2xl shadow-lg flex items-center gap-2">
                <Phone className="w-4 h-4" />
                Ligar Agora
              </Button>
              <Button
                size="lg"
                variant="secondary"
                className="px-8 rounded-2xl shadow-lg flex items-center gap-2 bg-white text-primary hover:bg-white/90"
              >
                <Calendar className="w-4 h-4" />
                {institution.type === "farmacia" ? "Reservar" : "Agendar Consulta"}
              </Button>
            </div>
          </div>
        </div>
      </section>

      {/* Content Grid */}
      <div className="max-w-6xl mx-auto px-6 py-12 grid grid-cols-1 lg:grid-cols-3 gap-8">
        {/* Left Column: Details & Map */}
        <div className="lg:col-span-1 space-y-8">
          {/* Description Card */}
          <div className="bg-card p-6 rounded-2xl shadow-sm border border-border/10">
            <h3 className="text-lg font-bold text-primary mb-4">Sobre</h3>
            <p className="text-sm text-muted-foreground leading-relaxed">
              {institution.description}
            </p>
          </div>

          {/* Stats for hospitals */}
          {(institution.type === "hospital" || institution.type === "posto") && (
            <div className="bg-card p-6 rounded-2xl shadow-sm border border-border/10">
              <h3 className="text-lg font-bold text-primary mb-4">Estatisticas</h3>
              <div className="grid grid-cols-2 gap-4">
                {institution.doctors && (
                  <div className="text-center p-4 bg-muted rounded-xl">
                    <Users className="w-6 h-6 text-primary mx-auto mb-2" />
                    <p className="text-2xl font-extrabold text-primary">{institution.doctors}</p>
                    <p className="text-xs text-muted-foreground">Medicos</p>
                  </div>
                )}
                {institution.beds && (
                  <div className="text-center p-4 bg-muted rounded-xl">
                    <Shield className="w-6 h-6 text-primary mx-auto mb-2" />
                    <p className="text-2xl font-extrabold text-primary">{institution.beds}</p>
                    <p className="text-xs text-muted-foreground">Camas</p>
                  </div>
                )}
              </div>
            </div>
          )}

          {/* Contact Info Card */}
          <div className="bg-card p-6 rounded-2xl shadow-sm border border-border/10">
            <h3 className="text-lg font-bold text-primary mb-6">Informacoes de Contacto</h3>
            <div className="space-y-6">
              <div className="flex gap-4">
                <div className="w-12 h-12 rounded-xl bg-muted flex items-center justify-center text-primary shrink-0">
                  <Clock className="w-5 h-5" />
                </div>
                <div>
                  <p className="text-sm font-bold text-foreground">Horario</p>
                  <p className="text-sm text-muted-foreground">{institution.hours}</p>
                </div>
              </div>
              <div className="flex gap-4">
                <div className="w-12 h-12 rounded-xl bg-muted flex items-center justify-center text-primary shrink-0">
                  <Phone className="w-5 h-5" />
                </div>
                <div>
                  <p className="text-sm font-bold text-foreground">Telefone</p>
                  <p className="text-sm text-muted-foreground">{institution.phone}</p>
                </div>
              </div>
              <div className="flex gap-4">
                <div className="w-12 h-12 rounded-xl bg-muted flex items-center justify-center text-primary shrink-0">
                  <Award className="w-5 h-5" />
                </div>
                <div>
                  <p className="text-sm font-bold text-foreground">Servicos</p>
                  <div className="flex flex-wrap gap-1 mt-1">
                    {institution.services.map((service, index) => (
                      <span key={index} className="text-[10px] bg-muted text-muted-foreground px-2 py-0.5 rounded-full">
                        {service}
                      </span>
                    ))}
                  </div>
                </div>
              </div>
            </div>
          </div>

          {/* Specialties for hospitals */}
          {institution.specialties && (
            <div className="bg-card p-6 rounded-2xl shadow-sm border border-border/10">
              <h3 className="text-lg font-bold text-primary mb-4">Especialidades</h3>
              <div className="flex flex-wrap gap-2">
                {institution.specialties.map((specialty, index) => (
                  <span key={index} className="text-xs bg-primary/10 text-primary px-3 py-1.5 rounded-full font-medium">
                    {specialty}
                  </span>
                ))}
              </div>
            </div>
          )}

          {/* Map Snippet */}
          <div className="relative h-64 rounded-2xl overflow-hidden bg-muted">
            <img
              src="https://images.unsplash.com/photo-1451187580459-43490279c0fa?w=600&h=400&fit=crop"
              alt="Mapa Satelite"
              className="w-full h-full object-cover"
            />
            <div className="absolute inset-0 bg-slate-900/20" />
            <div className="absolute inset-0 flex items-center justify-center">
              <div className={cn("w-12 h-12 rounded-full flex items-center justify-center text-white shadow-xl", 
                institution.type === "farmacia" ? "bg-blue-600" : 
                institution.type === "hospital" ? "bg-red-600" : "bg-green-600"
              )}>
                <TypeIcon className="w-5 h-5" />
              </div>
            </div>
            <Link 
              href={`https://maps.google.com/?q=${encodeURIComponent(institution.address)}`}
              target="_blank"
              className="absolute bottom-4 left-4 right-4 bg-white/90 backdrop-blur-md p-3 rounded-xl flex items-center justify-between cursor-pointer hover:bg-white transition-colors"
            >
              <span className="text-xs font-bold text-primary">Abrir no Google Maps</span>
              <ExternalLink className="w-4 h-4 text-primary" />
            </Link>
          </div>
        </div>

        {/* Right Column: Content based on type */}
        <div className="lg:col-span-2">
          {institution.type === "farmacia" ? (
            <>
              <div className="flex items-center justify-between mb-8">
                <h3 className="text-2xl font-extrabold text-blue-900 dark:text-blue-200 font-serif">
                  Medicamentos Disponiveis
                </h3>
                <div className="flex gap-2">
                  {filterTabs.map((tab) => (
                    <button
                      key={tab}
                      onClick={() => setActiveFilter(tab)}
                      className={`px-4 py-2 text-xs font-bold rounded-full cursor-pointer transition-colors ${
                        activeFilter === tab
                          ? "bg-secondary text-secondary-foreground"
                          : "bg-muted text-muted-foreground hover:bg-primary hover:text-primary-foreground"
                      }`}
                    >
                      {tab}
                    </button>
                  ))}
                </div>
              </div>

              <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                {medicines.map((medicine) => (
                  <MedicineCard
                    key={medicine.id}
                    medicine={medicine}
                    onAdd={(id) => console.log("Added:", id)}
                  />
                ))}
              </div>
            </>
          ) : (
            <>
              <div className="flex items-center justify-between mb-8">
                <h3 className="text-2xl font-extrabold text-blue-900 dark:text-blue-200 font-serif">
                  Servicos Disponiveis
                </h3>
              </div>

              <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                {institution.services.map((service, index) => (
                  <div key={index} className="bg-card p-6 rounded-2xl shadow-sm border border-border/10 hover:shadow-md transition-shadow">
                    <div className="flex items-start gap-4">
                      <div className={cn("w-12 h-12 rounded-xl flex items-center justify-center shrink-0",
                        institution.type === "hospital" ? "bg-red-100 text-red-600" : "bg-green-100 text-green-600"
                      )}>
                        <Stethoscope className="w-5 h-5" />
                      </div>
                      <div>
                        <h4 className="font-bold text-foreground mb-1">{service}</h4>
                        <p className="text-xs text-muted-foreground">
                          Disponivel de acordo com o horario de funcionamento
                        </p>
                        <Button variant="link" className="px-0 text-primary text-xs mt-2">
                          Saber mais
                        </Button>
                      </div>
                    </div>
                  </div>
                ))}
              </div>

              {/* Call to Action */}
              <div className="mt-8 bg-primary/5 p-8 rounded-2xl">
                <h4 className="text-xl font-bold text-primary mb-2">Precisa de uma consulta?</h4>
                <p className="text-muted-foreground mb-4">
                  Agende a sua consulta online ou ligue para marcar um horario.
                </p>
                <div className="flex gap-4">
                  <Button size="lg" className="rounded-xl">
                    <Calendar className="w-4 h-4 mr-2" />
                    Agendar Online
                  </Button>
                  <Button size="lg" variant="outline" className="rounded-xl">
                    <Phone className="w-4 h-4 mr-2" />
                    {institution.phone}
                  </Button>
                </div>
              </div>
            </>
          )}
        </div>
      </div>
    </div>
  )
}
