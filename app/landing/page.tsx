"use client"

import { useRef, useState, useEffect } from "react"
import Link from "next/link"
import { motion, useScroll, useTransform, AnimatePresence, useSpring } from "framer-motion"
import { 
  MapPin, Pill, Users, Star, Search, ArrowRightLeft, CheckCircle2, 
  Mic, MicOff, FileText, ArrowUpRight, Stethoscope, Building2, 
  HelpCircle, ArrowRight, ShieldCheck, PlusSquare, Clock, Building,
  Facebook, Twitter, Mail, X, UploadCloud
} from "lucide-react"

/* ── Animation Utilities ── */
const RevealOnScroll = ({ children, animation = "fadeIn", duration = 0.6 }: any) => {
  const variants: any = {
    fadeIn: { hidden: { opacity: 0 }, visible: { opacity: 1 } },
    slideUp: { hidden: { opacity: 0, y: 50 }, visible: { opacity: 1, y: 0 } },
    slideLeft: { hidden: { opacity: 0, x: -50 }, visible: { opacity: 1, x: 0 } },
    slideRight: { hidden: { opacity: 0, x: 50 }, visible: { opacity: 1, x: 0 } },
    zoomIn: { hidden: { opacity: 0, scale: 0.8 }, visible: { opacity: 1, scale: 1 } }
  }
  return (
    <motion.div
      initial="hidden" whileInView="visible" viewport={{ once: true, margin: "-10%" }}
      transition={{ duration, ease: [0.22, 1, 0.36, 1] }} variants={variants[animation]}
    >
      {children}
    </motion.div>
  )
}

const StaggerContainer = ({ children, className, staggerDelay = 0.1 }: any) => (
  <motion.div
    className={className} initial="hidden" whileInView="visible" viewport={{ once: true, margin: "-10%" }}
    variants={{ visible: { transition: { staggerChildren: staggerDelay } } }}
  >
    {children}
  </motion.div>
)

const StaggerItem = ({ children, animation = "fadeIn" }: any) => {
  const variants: any = {
    fadeIn: { hidden: { opacity: 0 }, visible: { opacity: 1, transition: { duration: 0.6, ease: [0.22, 1, 0.36, 1] } } },
    slideUp: { hidden: { opacity: 0, y: 40 }, visible: { opacity: 1, y: 0, transition: { duration: 0.6, ease: [0.22, 1, 0.36, 1] } } },
    slideLeft: { hidden: { opacity: 0, x: -40 }, visible: { opacity: 1, x: 0, transition: { duration: 0.6, ease: [0.22, 1, 0.36, 1] } } },
    slideRight: { hidden: { opacity: 0, x: 40 }, visible: { opacity: 1, x: 0, transition: { duration: 0.6, ease: [0.22, 1, 0.36, 1] } } },
    zoomIn: { hidden: { opacity: 0, scale: 0.9 }, visible: { opacity: 1, scale: 1, transition: { duration: 0.5, ease: [0.22, 1, 0.36, 1] } } }
  }
  return <motion.div variants={variants[animation]} className="h-full">{children}</motion.div>
}

const SectionWrapper = ({ children, orbs, orbTheme, className = "", ...props }: any) => {
  return (
    <div className={`relative scroll-mt-24 ${className}`} {...props}>
      {orbs && (
        <div className="absolute inset-0 overflow-hidden pointer-events-none z-0 flex items-center justify-center">
          {orbTheme === 'primary' && <div className="absolute w-[600px] h-[600px] bg-primary/5 rounded-full blur-[100px]" />}
          {orbTheme === 'secondary' && <div className="absolute w-[500px] h-[500px] bg-blue-500/5 rounded-full blur-[100px]" />}
          {orbTheme === 'mixed' && (
            <>
              <div className="absolute top-0 right-0 w-96 h-96 bg-primary/5 rounded-full blur-[80px]" />
              <div className="absolute bottom-0 left-0 w-96 h-96 bg-blue-500/5 rounded-full blur-[80px]" />
            </>
          )}
        </div>
      )}
      {children}
    </div>
  )
}

const ScrollProgress = () => {
  const { scrollYProgress } = useScroll()
  const scaleX = useSpring(scrollYProgress, { stiffness: 100, damping: 30, restDelta: 0.001 })
  return <motion.div className="fixed top-0 left-0 right-0 h-1 bg-primary z-50 origin-left" style={{ scaleX }} />
}

const PrescriptionUploadModal = ({ isOpen, onClose }: any) => {
  if (!isOpen) return null;
  return (
    <AnimatePresence>
      <div className="fixed inset-0 z-50 flex items-center justify-center p-4 bg-black/60 backdrop-blur-sm">
        <motion.div 
          initial={{ opacity: 0, scale: 0.95 }} animate={{ opacity: 1, scale: 1 }} exit={{ opacity: 0, scale: 0.95 }}
          className="bg-background rounded-3xl w-full max-w-md p-6 relative overflow-hidden shadow-2xl"
        >
          <button onClick={onClose} className="absolute top-4 right-4 p-2 text-muted-foreground hover:text-foreground">
            <X className="w-5 h-5" />
          </button>
          <div className="text-center space-y-2 mb-6 mt-4">
            <h3 className="text-2xl font-bold">Submeter Receita</h3>
            <p className="text-sm text-muted-foreground">Faça upload ou tire uma foto</p>
          </div>
          <div className="border-2 border-dashed border-border rounded-2xl p-10 flex flex-col items-center justify-center cursor-pointer hover:bg-muted/50 transition-colors">
            <UploadCloud className="w-12 h-12 text-primary/50 mb-4" />
            <p className="text-sm font-medium">Clique ou arraste o ficheiro</p>
            <p className="text-xs text-muted-foreground mt-2">PDF, JPG, PNG</p>
          </div>
        </motion.div>
      </div>
    </AnimatePresence>
  )
}

const stats = [
  { label: "Unidades de Saúde", value: "200+", icon: MapPin },
  { label: "Serviços e Medicamentos", value: "5k+", icon: Pill },
  { label: "Clientes Ativos", value: "15k+", icon: Users },
  { label: "Satisfação", value: "98%", icon: Star },
]

const steps = [
  { number: "01", title: "Pesquise", desc: "Digite o nome do medicamento que procura", icon: Search },
  { number: "02", title: "Compare", desc: "Veja preços e disponibilidade em várias farmácias", icon: ArrowRightLeft },
  { number: "03", title: "Reserve", desc: "Reserve o seu medicamento e levante na farmácia", icon: CheckCircle2 },
]

export default function LandingPage() {
  const [isModalOpen, setIsModalOpen] = useState(false)
  const [isListening, setIsListening] = useState(false)
  const [searchQuery, setSearchQuery] = useState("")

  /* ── Hero Parallax ── */
  const heroRef = useRef<HTMLDivElement>(null)
  const { scrollYProgress: heroProgress } = useScroll({ target: heroRef, offset: ["start start", "end start"] })

  const pharmY = useTransform(heroProgress, [0, 1], [0, 120])
  const pharmOpacity = useTransform(heroProgress, [0, 0.6], [0.05, 0])
  const orb1Y = useTransform(heroProgress, [0, 1], [0, 80])
  const orb2Y = useTransform(heroProgress, [0, 1], [0, -60])
  const orb3Y = useTransform(heroProgress, [0, 1], [0, 50])
  const heroContentY = useTransform(heroProgress, [0, 1], [0, -40])
  const heroImageY = useTransform(heroProgress, [0, 1], [0, 30])

  const handleVoiceSearch = () => {
    setIsListening(true)
    setTimeout(() => { setSearchQuery("Paracetamol 500mg"); setIsListening(false) }, 2000)
  }

  return (
    <div className="bg-background min-h-screen text-foreground font-sans overflow-x-hidden">
      <ScrollProgress />
      <PrescriptionUploadModal isOpen={isModalOpen} onClose={() => setIsModalOpen(false)} />

      {/* ════════════════════════════════════════
          NAVBAR
         ════════════════════════════════════════ */}
      <motion.nav 
        initial={{ y: -100 }}
        animate={{ y: 0 }}
        transition={{ duration: 0.6, ease: [0.22, 1, 0.36, 1] }}
        className="fixed top-0 inset-x-0 z-40 bg-background/80 backdrop-blur-md border-b border-border/50"
      >
        <div className="max-w-[1400px] mx-auto px-6 h-20 flex items-center justify-between">
          <Link href="/landing" className="flex items-center gap-2 text-xl font-bold font-serif text-primary">
            <Pill className="w-6 h-6" />
            Apothecary
          </Link>
          
          <div className="hidden md:flex items-center gap-8 text-sm font-medium text-muted-foreground">
            <Link href="#inicio" className="hover:text-primary transition-colors">Início</Link>
            <Link href="#como-funciona" className="hover:text-primary transition-colors">Como Funciona</Link>
            <Link href="#rede" className="hover:text-primary transition-colors">Rede</Link>
            <Link href="#contactos" className="hover:text-primary transition-colors">Contactos</Link>
          </div>

          <div className="flex items-center gap-4">
            <Link href="/login" className="text-sm font-bold hover:text-primary transition-colors hidden sm:block">
              Entrar
            </Link>
            <Link href="/login?tab=register" className="bg-primary text-primary-foreground px-5 py-2.5 rounded-full text-sm font-bold shadow-md hover:shadow-lg hover:scale-105 transition-all inline-block">
              Registar
            </Link>
          </div>
        </div>
      </motion.nav>

      {/* ════════════════════════════════════════
          HERO SECTION — Parallax
         ════════════════════════════════════════ */}
      <section id="inicio" ref={heroRef} className="relative w-full overflow-hidden pt-32 pb-24 lg:min-h-screen lg:flex lg:flex-col lg:justify-center bg-background">
        {/* Video Background */}
        <div className="absolute inset-0 z-0 pointer-events-none">
          <video autoPlay loop muted playsInline className="absolute inset-0 w-full h-full object-cover opacity-[0.04]">
            <source src="https://cdn.pixabay.com/video/2021/08/17/85303-588383856_large.mp4" type="video/mp4" />
          </video>
        </div>

        {/* Animated Orbs */}
        <div className="absolute inset-0 overflow-hidden pointer-events-none z-0">
          <motion.div style={{ y: orb1Y }} className="absolute top-0 right-0 w-96 h-96 bg-primary/10 rounded-full blur-3xl animate-pulse" />
          <motion.div style={{ y: orb2Y }} className="absolute bottom-0 left-0 w-96 h-96 bg-blue-500/10 rounded-full blur-3xl animate-pulse" />
          <motion.div style={{ y: orb3Y }} className="absolute top-1/2 left-1/4 w-72 h-72 bg-primary/5 rounded-full blur-3xl animate-pulse" />
        </div>

        {/* PHARM Background Text */}
        <motion.div style={{ y: pharmY, opacity: pharmOpacity }} className="absolute -bottom-10 left-0 w-full overflow-hidden leading-none select-none pointer-events-none z-0 flex justify-center">
          <span className="text-[40vw] sm:text-[35vw] font-black text-primary tracking-tighter translate-y-[15%] whitespace-nowrap opacity-50">
            PHARM
          </span>
        </motion.div>

        {/* Hero Content */}
        <motion.div style={{ y: heroContentY }} className="max-w-[1400px] mx-auto px-6 relative z-10 w-full py-12 lg:py-0">
          <div className="grid grid-cols-1 lg:grid-cols-2 gap-12 lg:gap-16 items-center">
            
            {/* LEFT CONTENT */}
            <motion.div
              initial="hidden" animate="visible"
              variants={{ hidden: {}, visible: { transition: { staggerChildren: 0.12, delayChildren: 0.1 } } }}
              className="flex flex-col justify-center space-y-8 pt-4 lg:pt-0"
            >
              <motion.div variants={{ hidden: { opacity: 0, y: 40 }, visible: { opacity: 1, y: 0, transition: { duration: 0.7 } } }}
                className="space-y-4"
              >
                <h1 className="text-5xl md:text-6xl lg:text-7xl font-black text-foreground leading-[1.1] tracking-tighter">
                  A sua saúde <br />
                  <span className="text-primary">em primeiro lugar</span>
                </h1>
              </motion.div>

              <motion.p variants={{ hidden: { opacity: 0, y: 30 }, visible: { opacity: 1, y: 0, transition: { duration: 0.6 } } }}
                className="text-lg lg:text-xl text-muted-foreground font-light max-w-lg leading-relaxed"
              >
                Acesso imediato a hospitais, clínicas e farmácias. Verifique disponibilidades, encontre especialidades médicas e compre com confiança.
              </motion.p>

              {/* Search / CTA */}
              <motion.div variants={{ hidden: { opacity: 0, y: 30 }, visible: { opacity: 1, y: 0, transition: { duration: 0.6 } } }}
                className="flex flex-col gap-4 pt-2"
              >
                <div className="flex flex-col sm:flex-row gap-3 items-stretch sm:items-center bg-card rounded-2xl shadow-xl border border-border p-2">
                  <div className="flex items-center px-4 text-muted-foreground">
                    <Search className="w-5 h-5" />
                  </div>
                  <input
                    className="flex-1 bg-transparent outline-none text-sm font-medium py-3 px-2 placeholder:text-muted-foreground/50"
                    placeholder={isListening ? "A escutar..." : "Ex: Paracetamol, Clínica..."}
                    type="text" value={searchQuery} onChange={(e) => setSearchQuery(e.target.value)}
                  />
                  <button
                    onClick={handleVoiceSearch}
                    className={`p-3 rounded-xl flex items-center justify-center transition-colors ${isListening ? "bg-destructive/10 text-destructive animate-pulse" : "text-primary hover:bg-primary/10"}`}
                  >
                    {isListening ? <Mic className="w-5 h-5" /> : <MicOff className="w-5 h-5" />}
                  </button>
                  <Link href="/login?redirect=/pesquisa" className="bg-primary text-primary-foreground px-6 py-3 rounded-xl text-sm font-bold hover:opacity-90 flex items-center justify-center whitespace-nowrap">
                    Procurar
                  </Link>
                </div>

                <div className="flex gap-3">
                  <Link href="/login?redirect=/receitas" className="inline-flex items-center gap-2 bg-muted/50 border border-border/50 hover:bg-muted text-foreground px-5 py-3 rounded-xl text-sm font-bold transition-all shadow-sm w-fit">
                    <FileText className="w-4 h-4 text-primary" /> Submeter Receita
                  </Link>
                </div>
              </motion.div>
            </motion.div>

            {/* RIGHT VISUAL */}
            <motion.div style={{ y: heroImageY }} className="relative justify-end h-full mt-12 lg:mt-0 hidden lg:flex items-end">
              <div className="relative w-full flex items-end h-full">
                <div className="relative z-10 w-full max-w-[750px] h-full flex items-end pointer-events-none">
                  <img src="https://nationalhealthcare.co.za/wp-content/uploads/2020/08/healthcare-providers2-2.png" alt="Profissional" className="w-full object-contain hover:scale-105 transition-transform duration-700 pointer-events-auto filter drop-shadow-2xl" />
                </div>
              </div>
              
              {/* Floating Card */}
              <motion.div
                initial={{ opacity: 0, y: 40, x: -20 }} animate={{ opacity: 1, y: 0, x: 0 }} transition={{ delay: 0.8, duration: 0.7 }}
                className="absolute bottom-24 -left-8 z-20 bg-card p-6 shadow-2xl max-w-xs border border-border rounded-2xl backdrop-blur-sm"
              >
                <div className="flex justify-between items-start mb-4">
                  <div className="flex items-center gap-2">
                    <span className="w-2 h-2 bg-primary rounded-full animate-ping" />
                    <span className="bg-green-500/10 text-green-600 text-[10px] font-bold px-3 py-1 rounded-full uppercase">Destaque</span>
                  </div>
                  <ArrowUpRight className="w-5 h-5 text-muted-foreground" />
                </div>
                <div className="flex items-center gap-4">
                  <div className="w-14 h-14 bg-primary/10 rounded-xl flex items-center justify-center shrink-0">
                    <Pill className="w-6 h-6 text-primary" />
                  </div>
                  <div>
                    <p className="text-sm font-bold text-foreground leading-tight">Vitamina C + Zinco</p>
                    <p className="text-xs text-muted-foreground mt-1">Premium Imunidade</p>
                    <p className="text-sm font-black text-primary mt-2">Kz 2,000</p>
                  </div>
                </div>
              </motion.div>
            </motion.div>
          </div>
        </motion.div>
      </section>

      {/* ════════════════════════════════════════
          PILARES DO ATENDIMENTO / COMO FUNCIONA
         ════════════════════════════════════════ */}
      <SectionWrapper orbs orbTheme="secondary" className="bg-slate-900 overflow-hidden pt-24 pb-32" id="como-funciona">
        <section className="px-6 max-w-7xl mx-auto">
          <RevealOnScroll animation="slideUp">
            <div className="mb-16 text-center">
              <span className="inline-block bg-primary/10 text-primary px-4 py-2 rounded-full text-xs font-bold mb-4 uppercase tracking-widest">Conheça os Nossos</span>
              <h2 className="text-4xl md:text-5xl font-black text-white mb-4">Pilares do Atendimento</h2>
              <div className="w-24 h-2 bg-primary mx-auto rounded-full mt-4" />
            </div>
          </RevealOnScroll>

          <StaggerContainer className="grid md:grid-cols-3 gap-6" staggerDelay={0.15}>
            {[
              { icon: Stethoscope, title: "Rede de Farmácias", desc: "Encontre farmácias licenciadas próximas à sua localização com estoque atualizado em tempo real.", link: "Consultar Stock", color: "text-primary", bg: "bg-primary/10", groupBg: "group-hover:bg-primary/20", border: "hover:border-primary/50" },
              { icon: Building2, title: "Hospitais e Centros", desc: "Status em tempo real das unidades de saúde públicas e privadas. Verifique tempos de espera.", link: "Ver Unidades", color: "text-blue-400", bg: "bg-blue-500/10", groupBg: "group-hover:bg-blue-500/20", border: "hover:border-blue-500/50" },
              { icon: HelpCircle, title: "Guia de Sintomas", desc: "Orientações oficiais validadas pelo Ministério da Saúde sobre problemas comuns e protocolos.", link: "Iniciar Triagem", color: "text-primary", bg: "bg-primary/10", groupBg: "group-hover:bg-primary/20", border: "hover:border-primary/50" }
            ].map((pilar, i) => (
              <StaggerItem key={i} animation={i === 0 ? "slideLeft" : i === 1 ? "slideUp" : "slideRight"}>
                <div className={`group relative bg-slate-800/80 rounded-2xl p-8 border border-white/5 shadow-xl transition-all duration-300 h-full ${pilar.border} backdrop-blur-md`}>
                  <div className="relative z-10">
                    <div className={`w-14 h-14 ${pilar.bg} rounded-2xl flex items-center justify-center mb-6 transition-colors ${pilar.groupBg}`}>
                      <pilar.icon className={`w-6 h-6 ${pilar.color}`} />
                    </div>
                    <h3 className="text-xl font-bold text-white mb-3">{pilar.title}</h3>
                    <p className="text-sm text-slate-300 leading-relaxed mb-6">{pilar.desc}</p>
                    <a className={`inline-flex items-center gap-2 ${pilar.color} font-bold text-sm hover:gap-4 transition-all`} href="#">
                      {pilar.link} <ArrowRight className="w-4 h-4" />
                    </a>
                  </div>
                </div>
              </StaggerItem>
            ))}
          </StaggerContainer>
        </section>
      </SectionWrapper>

      {/* ════════════════════════════════════════
          STATS
         ════════════════════════════════════════ */}
      <SectionWrapper className="bg-background border-b border-border/50">
        <section className="py-20 px-6">
          <div className="max-w-7xl mx-auto">
            <StaggerContainer className="grid grid-cols-2 lg:grid-cols-4 gap-8" staggerDelay={0.12}>
              {stats.map((stat, i) => (
                <StaggerItem key={stat.label} animation="zoomIn">
                  <div className="text-center">
                    <div className="flex justify-center mb-4">
                      <div className="w-16 h-16 bg-primary/10 rounded-2xl flex items-center justify-center">
                        <stat.icon className="w-7 h-7 text-primary" />
                      </div>
                    </div>
                    <p className="text-4xl md:text-5xl font-black text-foreground mb-2">{stat.value}</p>
                    <p className="text-sm text-muted-foreground uppercase tracking-widest font-bold">{stat.label}</p>
                  </div>
                </StaggerItem>
              ))}
            </StaggerContainer>
          </div>
        </section>
      </SectionWrapper>

      {/* ════════════════════════════════════════
          HOW IT WORKS
         ════════════════════════════════════════ */}
      <SectionWrapper orbs orbTheme="secondary" className="bg-muted/30 overflow-hidden relative">
        <section className="py-24 px-6 relative z-10">
          <div className="max-w-6xl mx-auto">
            <RevealOnScroll animation="slideUp">
              <div className="text-center mb-16">
                <span className="inline-block bg-primary/10 text-primary px-4 py-2 rounded-full text-xs font-bold mb-4 uppercase tracking-widest">Processo</span>
                <h2 className="text-4xl md:text-5xl font-black text-foreground mb-4">Como <span className="text-primary">funciona</span> a plataforma</h2>
                <p className="text-muted-foreground max-w-2xl mx-auto text-lg font-light">Um processo simples e intuitivo em apenas três passos.</p>
              </div>
            </RevealOnScroll>

            <div className="grid grid-cols-1 md:grid-cols-3 gap-8 relative">
              {/* Connection line */}
              <div className="hidden md:block absolute top-20 left-0 w-full h-1 bg-gradient-to-r from-primary/10 via-primary/20 to-primary/10" />

              <StaggerContainer className="grid grid-cols-1 md:grid-cols-3 gap-8 col-span-full" staggerDelay={0.18}>
                {steps.map((s, idx) => (
                  <StaggerItem key={s.number} animation="slideRight">
                    <div className="relative h-full">
                      <div className="bg-card rounded-2xl p-8 border border-border shadow-sm hover:shadow-xl hover:border-primary/30 transition-all relative z-10 h-full">
                        <div className="flex items-center gap-4 mb-6">
                          <div className="w-16 h-16 bg-primary/10 rounded-2xl flex items-center justify-center shrink-0">
                            <s.icon className="w-7 h-7 text-primary" />
                          </div>
                          <div className="text-4xl font-black text-primary/20">{s.number}</div>
                        </div>
                        <h3 className="text-2xl font-bold text-foreground mb-3">{s.title}</h3>
                        <p className="text-muted-foreground leading-relaxed">{s.desc}</p>
                      </div>
                      {idx < steps.length - 1 && (
                        <div className="hidden md:block absolute -right-4 top-12 z-20 bg-background rounded-full p-1">
                          <ArrowRight className="text-primary/30 w-8 h-8" />
                        </div>
                      )}
                    </div>
                  </StaggerItem>
                ))}
              </StaggerContainer>
            </div>
          </div>
        </section>
      </SectionWrapper>

      {/* ════════════════════════════════════════
          CTA
         ════════════════════════════════════════ */}
      <SectionWrapper orbs orbTheme="primary" className="bg-background">
        <section className="py-24 px-6 relative overflow-hidden">
          <RevealOnScroll animation="zoomIn">
            <div className="max-w-4xl mx-auto relative z-10 text-center">
              <span className="inline-block bg-primary/10 text-primary px-4 py-2 rounded-full text-xs font-bold mb-6 uppercase tracking-widest">Pronto para começar</span>
              <h2 className="text-4xl md:text-5xl font-black text-foreground mb-6">Encontre medicamentos com <span className="text-primary">confiança</span></h2>
              <p className="text-lg text-muted-foreground max-w-2xl mx-auto mb-10 font-light leading-relaxed">
                Junte-se a milhares de angolanos que já confiam na nossa rede de saúde integrada. Encontre clínicas, hospitais e farmácias com facilidade.
              </p>
              <Link href="/pesquisa" className="inline-flex items-center gap-3 bg-primary text-primary-foreground px-10 py-4 rounded-xl text-base font-bold hover:opacity-90 transition-all hover:shadow-lg hover:scale-105">
                <Search className="w-5 h-5" /> Começar Pesquisa Agora
              </Link>
            </div>
          </RevealOnScroll>
        </section>
      </SectionWrapper>

      {/* ════════════════════════════════════════
          TRUST
         ════════════════════════════════════════ */}
      <SectionWrapper orbs orbTheme="secondary" className="bg-slate-900 pt-20 pb-20" id="rede">
        <section className="px-6 text-white max-w-7xl mx-auto">
          <StaggerContainer className="grid grid-cols-1 md:grid-cols-3 gap-8" staggerDelay={0.14}>
            {[
              { icon: ShieldCheck, title: "100% Seguro", desc: "Dados criptografados e transações protegidas." },
              { icon: PlusSquare, title: "Farmácias Verificadas", desc: "Apenas parceiros certificados e confiáveis." },
              { icon: Clock, title: "Entrega Rápida", desc: "Levante ou entrega em até 24 horas." }
            ].map((t, i) => (
              <StaggerItem key={i} animation="slideUp">
                <div className="text-center p-8 bg-white/5 rounded-2xl border border-white/10 h-full backdrop-blur-md">
                  <t.icon className="w-10 h-10 text-primary mx-auto mb-4" />
                  <h3 className="text-lg font-bold mb-2">{t.title}</h3>
                  <p className="text-sm text-white/70">{t.desc}</p>
                </div>
              </StaggerItem>
            ))}
          </StaggerContainer>
        </section>
      </SectionWrapper>

      {/* ════════════════════════════════════════
          PARTNER PHARMACIES 
         ════════════════════════════════════════ */}
      <SectionWrapper className="bg-background">
        <section className="py-24 px-6">
          <div className="max-w-7xl mx-auto">
            <RevealOnScroll animation="slideRight">
              <div className="flex flex-col md:flex-row justify-between items-start md:items-end gap-8 mb-16">
                <div className="max-w-2xl">
                  <span className="inline-block bg-primary/10 text-primary px-4 py-2 rounded-full text-xs font-bold mb-4 uppercase tracking-widest">Rede de Saúde</span>
                  <h2 className="text-4xl md:text-5xl font-black text-foreground mb-4">Nossa <span className="text-primary">Rede Integrada</span></h2>
                  <p className="text-muted-foreground text-lg max-w-xl font-light">
                    Acesso imediato a hospitais, clínicas e farmácias. Compare disponibilidade, especialidades e garanta os serviços de que precisa.
                  </p>
                </div>
                <Link href="/farmacias" className="px-8 py-4 border-2 border-border bg-card text-foreground font-bold text-sm uppercase tracking-wider hover:border-primary hover:text-primary transition-all hover:shadow-lg whitespace-nowrap rounded-xl">
                  Ver Toda a Rede →
                </Link>
              </div>
            </RevealOnScroll>

            <StaggerContainer className="grid grid-cols-1 md:grid-cols-3 gap-8" staggerDelay={0.16}>
              {[
                { type: "farmacia", name: "Farmácia Central", loc: "Luanda, Maianga", dist: "1.2 km", status: "Ativa", rate: "4.8", time: "24h", imgIcon: PlusSquare, bgs: "from-primary/20 to-primary/5", tBg: "bg-primary", tTxt: "text-primary", tClr: "text-primary", tags: ["Entrega 24h", "5k+ Produtos"] },
                { type: "clinica", name: "Clínica Vida", loc: "Luanda, Maianga", dist: "2.5 km", status: "Aberta", rate: "4.6", time: "8h - 22h", imgIcon: Stethoscope, bgs: "from-blue-500/20 to-blue-500/5", tBg: "bg-blue-500", tTxt: "text-blue-500", tClr: "text-blue-500", tags: ["Exames", "15+ Especialidades"] },
                { type: "hospital", name: "Hospital M.D.", loc: "Luanda, Talatona", dist: "3.8 km", status: "Urgências", rate: "4.9", time: "24h", imgIcon: Building, bgs: "from-purple-500/20 to-purple-500/5", tBg: "bg-purple-500", tTxt: "text-purple-500", tClr: "text-purple-500", tags: ["Urgência 24h", "150+ Leitos"] }
              ].map((p, i) => (
                <StaggerItem key={i} animation={i === 0 ? "slideLeft" : i === 1 ? "slideUp" : "slideRight"}>
                  <div className="group cursor-pointer bg-card rounded-2xl overflow-hidden shadow-sm hover:shadow-2xl transition-all duration-300 border border-border">
                    <div className="h-56 relative overflow-hidden bg-muted">
                      <div className={`w-full h-full bg-gradient-to-br flex items-center justify-center ${p.bgs}`}>
                        <p.imgIcon className={`w-24 h-24 opacity-20 ${p.tTxt}`} />
                      </div>
                      <div className="absolute inset-0 bg-gradient-to-t from-black/80 via-black/20 to-transparent" />
                      <div className="absolute bottom-6 left-6 text-white right-0 pr-6">
                        <p className="font-black text-2xl mb-1">{p.name}</p>
                        <p className="text-sm opacity-90 flex items-center gap-1.5"><MapPin className="w-4 h-4" /> {p.loc}</p>
                      </div>
                      <div className="absolute top-6 right-6 bg-slate-900 text-white px-3 py-1.5 text-xs font-black rounded-lg shadow-lg">{p.dist}</div>
                      <div className={`absolute top-6 left-6 ${p.tBg} text-white px-3 py-1.5 text-xs font-bold rounded-lg shadow-lg uppercase tracking-widest`}>{p.status}</div>
                    </div>
                    <div className="p-6">
                      <div className="flex items-center justify-between mb-6">
                        <div className="flex items-center gap-4">
                          <div className="flex items-center gap-1.5"><Star className="w-4 h-4 text-yellow-500 fill-yellow-500" /><span className="font-bold">{p.rate}</span></div>
                          <div className="w-px h-6 bg-border" />
                          <div className="flex items-center gap-1.5"><Clock className="w-4 h-4 text-muted-foreground" /><span className="text-sm font-medium">{p.time}</span></div>
                        </div>
                        <div className="w-10 h-10 rounded-full bg-muted flex items-center justify-center group-hover:bg-primary group-hover:text-primary-foreground transition-all">
                          <ArrowRight className="w-5 h-5" />
                        </div>
                      </div>
                      <div className="flex gap-2">
                        {p.tags.map(tag => (
                          <span key={tag} className="text-xs bg-muted text-foreground font-bold px-3 py-1 rounded-full">{tag}</span>
                        ))}
                      </div>
                    </div>
                  </div>
                </StaggerItem>
              ))}
            </StaggerContainer>
          </div>
        </section>
      </SectionWrapper>

      {/* ════════════════════════════════════════
          FOOTER
         ════════════════════════════════════════ */}
      <SectionWrapper className="bg-slate-950 text-white" id="contactos">
        <RevealOnScroll animation="fadeIn" duration={0.8}>
          <footer className="py-16 px-6">
            <div className="max-w-7xl mx-auto">
              <div className="grid grid-cols-1 md:grid-cols-4 gap-12 mb-12">
                <div>
                  <h3 className="text-2xl font-black mb-4">Apothecary <span className="text-primary">Angola</span></h3>
                  <p className="text-white/70 text-sm mb-6">A plataforma mais confiável para encontrar medicamentos em Angola.</p>
                  <div className="flex gap-4">
                    <a href="#" className="w-10 h-10 bg-white/10 rounded-lg flex items-center justify-center hover:bg-primary transition-colors"><Facebook className="w-4 h-4" /></a>
                    <a href="#" className="w-10 h-10 bg-white/10 rounded-lg flex items-center justify-center hover:bg-primary transition-colors"><Twitter className="w-4 h-4" /></a>
                    <a href="#" className="w-10 h-10 bg-white/10 rounded-lg flex items-center justify-center hover:bg-primary transition-colors"><Mail className="w-4 h-4" /></a>
                  </div>
                </div>
                {[
                  { title: "Produto", links: ["Pesquisar", "Farmácias", "Preços", "Blog"] },
                  { title: "Empresa", links: ["Sobre Nós", "Contacto", "Carreiras", "Imprensa"] },
                  { title: "Legal", links: ["Privacidade", "Termos de Uso", "Cookies", "Compliance"] }
                ].map((col, i) => (
                  <div key={i}>
                    <h4 className="font-bold text-white mb-4 uppercase text-xs tracking-widest">{col.title}</h4>
                    <ul className="space-y-3 text-sm">
                      {col.links.map(l => (
                        <li key={l}><a href="#" className="text-white/70 hover:text-primary transition-colors">{l}</a></li>
                      ))}
                    </ul>
                  </div>
                ))}
              </div>
              <div className="border-t border-white/10 pt-8 flex flex-col md:flex-row items-center justify-between gap-4">
                <p className="text-sm text-white/50">© 2026 Apothecary Angola. Todos os direitos reservados.</p>
                <p className="text-sm text-white/50">Desenvolvido com ❤️ para Angola</p>
              </div>
            </div>
          </footer>
        </RevealOnScroll>
      </SectionWrapper>
    </div>
  )
}