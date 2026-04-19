"use client"

import { useState, useRef } from "react"
import Link from "next/link"
import { motion, useScroll, useTransform } from "framer-motion"
import { Search, Mic, MicOff, MapPin, Pill, Users, Star, ArrowRight, ArrowUpRight, CheckCircle2, ShieldCheck, Building2, Stethoscope, Mail, Clock } from "lucide-react"
import { Button } from "@/components/ui/button"
import { Input } from "@/components/ui/input"
import { ScrollProgress, RevealOnScroll, StaggerContainer, StaggerItem } from "@/components/layout/animations"

const stats = [
  { label: "Unidades de Saúde", value: "200+", icon: MapPin },
  { label: "Serviços e Medicamentos", value: "5k+", icon: Pill },
  { label: "Clientes Ativos", value: "15k+", icon: Users },
  { label: "Satisfação", value: "98%", icon: Star },
]

const steps = [
  {
    number: "01",
    title: "Pesquise",
    desc: "Digite o nome do medicamento que procura",
    icon: Search,
  },
  {
    number: "02",
    title: "Compare",
    desc: "Veja preços e disponibilidade em várias farmácias",
    icon: ArrowRight,
  },
  {
    number: "03",
    title: "Reserve",
    desc: "Reserve o seu medicamento e levante na farmácia",
    icon: CheckCircle2,
  },
]

export default function IndexPage() {
  const [isListening, setIsListening] = useState(false)
  const [searchQuery, setSearchQuery] = useState("")

  const heroRef = useRef<HTMLDivElement>(null)
  const { scrollYProgress: heroProgress } = useScroll({
    target: heroRef,
    offset: ["start start", "end start"],
  })

  // PHARM text moves down as user scrolls
  const pharmY = useTransform(heroProgress, [0, 1], [0, 120])
  const pharmOpacity = useTransform(heroProgress, [0, 0.6], [0.05, 0])
  // Orbs react to scroll
  const orb1Y = useTransform(heroProgress, [0, 1], [0, 80])
  const orb2Y = useTransform(heroProgress, [0, 1], [0, -60])
  const orb3Y = useTransform(heroProgress, [0, 1], [0, 50])
  // Hero content parallax — subtle lift
  const heroContentY = useTransform(heroProgress, [0, 1], [0, -40])
  // Hero image parallax
  const heroImageY = useTransform(heroProgress, [0, 1], [0, 30])

  const worksRef = useRef<HTMLDivElement>(null)

  const handleVoiceSearch = () => {
    setIsListening(true)
    setTimeout(() => {
      setSearchQuery("Paracetamol 500mg")
      setIsListening(false)
    }, 2000)
  }

  return (
    <div className="min-h-screen bg-background">
      <ScrollProgress />
      
      {/* HERO SECTION */}
      <section
        ref={heroRef}
        className="relative w-full overflow-hidden pt-16 pb-0 lg:min-h-screen lg:flex lg:flex-col lg:justify-center bg-background"
      >
        {/* Video Background */}
        <div className="absolute inset-0 z-0 pointer-events-none">
          <video
            autoPlay
            loop
            muted
            playsInline
            className="absolute inset-0 w-full h-full object-cover opacity-[0.03]"
          >
            <source
              src="https://cdn.pixabay.com/video/2021/08/17/85303-588383856_large.mp4"
              type="video/mp4"
            />
          </video>
        </div>

        {/* Animated Orbs */}
        <div className="absolute inset-0 overflow-hidden pointer-events-none z-0">
          <motion.div
            style={{ y: orb1Y }}
            className="absolute top-0 right-0 w-96 h-96 bg-primary/5 rounded-full blur-3xl animate-pulse"
          />
          <motion.div
            style={{ y: orb2Y }}
            className="absolute bottom-0 left-0 w-96 h-96 bg-secondary/5 rounded-full blur-3xl animate-pulse"
          />
          <motion.div
            style={{ y: orb3Y }}
            className="absolute top-1/2 left-1/4 w-72 h-72 bg-primary/5 rounded-full blur-3xl animate-pulse"
          />
        </div>

        {/* PHARM Background Text */}
        <motion.div
          style={{ y: pharmY, opacity: pharmOpacity }}
          className="absolute bottom-0 left-0 w-full overflow-hidden leading-none select-none pointer-events-none z-0 flex justify-center"
        >
          <span className="text-[55vw] font-black text-primary tracking-tighter translate-y-[20%] whitespace-nowrap">
            PHARM
          </span>
        </motion.div>

        {/* Hero Content */}
        <motion.div
          style={{ y: heroContentY }}
          className="max-w-[1400px] mx-auto px-6 relative z-10 w-full py-12 lg:py-0"
        >
          <div className="grid grid-cols-1 lg:grid-cols-2 gap-12 lg:gap-16 items-center lg:h-screen">
            {/* LEFT CONTENT */}
            <motion.div
              initial="hidden"
              animate="visible"
              variants={{
                hidden: {},
                visible: { transition: { staggerChildren: 0.12, delayChildren: 0.1 } },
              }}
              className="flex flex-col justify-center space-y-8 pt-4 lg:pt-0"
            >
              {/* Badge */}
              <motion.div
                variants={{
                  hidden: { opacity: 0, y: 30 },
                  visible: { opacity: 1, y: 0, transition: { duration: 0.6, ease: [0.22, 1, 0.36, 1] } },
                }}
                className="inline-flex items-center gap-3 bg-primary/5 border border-primary/20 px-4 py-2 w-fit rounded-full hover:border-primary/40 transition-all duration-300 hover:shadow-sm"
              >
                <span className="w-2 h-2 bg-primary rounded-full animate-pulse" />
                <span className="text-primary text-xs font-bold uppercase tracking-widest">
                  ✓ Entrega em 24h • Luanda
                </span>
              </motion.div>

              {/* Headline */}
              <motion.div
                variants={{
                  hidden: { opacity: 0, y: 40 },
                  visible: { opacity: 1, y: 0, transition: { duration: 0.7, ease: [0.22, 1, 0.36, 1] } },
                }}
                className="space-y-4"
              >
                <h1 className="text-5xl md:text-6xl lg:text-7xl font-black text-foreground leading-[1.1] tracking-tighter">
                  A sua saúde <br />
                  <span className="text-primary">em primeiro lugar</span>
                </h1>
              </motion.div>

              {/* Description */}
              <motion.p
                variants={{
                  hidden: { opacity: 0, y: 30 },
                  visible: { opacity: 1, y: 0, transition: { duration: 0.6, ease: [0.22, 1, 0.36, 1] } },
                }}
                className="text-lg lg:text-xl text-muted-foreground font-light max-w-lg leading-relaxed"
              >
                Acesso imediato a hospitais, clínicas e farmácias. Verifique
                disponibilidades, encontre especialidades médicas e compre com
                confiança na maior plataforma de saúde de Angola.
              </motion.p>

              {/* Search / CTA */}
              <motion.div
                variants={{
                  hidden: { opacity: 0, y: 30 },
                  visible: { opacity: 1, y: 0, transition: { duration: 0.6, ease: [0.22, 1, 0.36, 1] } },
                }}
                className="flex flex-col gap-4 pt-2"
              >
                <div className="flex flex-col sm:flex-row gap-3 items-stretch sm:items-center bg-card rounded-2xl shadow-xl border border-border p-2 hover:shadow-2xl hover:border-primary/20 transition-all duration-300">
                  <div className="flex items-center px-4 text-muted-foreground">
                    <Search className="w-5 h-5" />
                  </div>
                  <Input
                    className="flex-1 bg-transparent border-0 ring-0 hover:ring-0 focus-visible:ring-0 focus-visible:ring-offset-0 text-sm font-medium py-3 px-2 shadow-none"
                    placeholder={isListening ? "A escutar..." : "Ex: Paracetamol, Clínica Pediátrica..."}
                    value={searchQuery}
                    onChange={(e) => setSearchQuery(e.target.value)}
                  />
                  <button
                    onClick={handleVoiceSearch}
                    className={`p-2 mr-2 rounded-xl flex items-center justify-center transition-colors ${
                      isListening
                        ? "bg-destructive/10 text-destructive animate-pulse"
                        : "text-primary hover:bg-primary/10"
                    }`}
                  >
                    {isListening ? <Mic className="w-5 h-5" /> : <MicOff className="w-5 h-5" />}
                  </button>
                  <Button asChild className="bg-primary text-primary-foreground px-6 py-6 rounded-xl text-sm font-bold hover:shadow-lg hover:scale-[1.02] transition-all whitespace-nowrap">
                    <Link href="/pesquisa">
                      Procurar
                    </Link>
                  </Button>
                </div>

                <div className="flex gap-3">
                  <Button asChild variant="outline" className="inline-flex items-center gap-2 bg-card border-border hover:bg-muted text-foreground px-5 py-6 rounded-xl text-sm font-bold transition-all shadow-sm w-fit">
                    <Link href="/receitas">
                      <ScrollViewIcon />
                      Submeter Receita
                    </Link>
                  </Button>
                </div>
              </motion.div>

              {/* Mini Stats */}
              <motion.div
                variants={{
                  hidden: { opacity: 0, y: 20 },
                  visible: { opacity: 1, y: 0, transition: { duration: 0.5, ease: [0.22, 1, 0.36, 1] } },
                }}
                className="grid grid-cols-3 gap-4 pt-8 border-t border-border"
              >
                <div className="group">
                  <p className="text-3xl lg:text-4xl font-black text-foreground group-hover:text-primary transition-colors">
                    200+
                  </p>
                  <p className="text-xs text-muted-foreground uppercase tracking-widest font-semibold mt-1">
                    Unidades
                  </p>
                </div>
                <div className="group">
                  <p className="text-3xl lg:text-4xl font-black text-foreground group-hover:text-primary transition-colors">
                    5k+
                  </p>
                  <p className="text-xs text-muted-foreground uppercase tracking-widest font-semibold mt-1">
                    Medicamentos
                  </p>
                </div>
                <div className="group">
                  <p className="text-3xl lg:text-4xl font-black text-foreground group-hover:text-primary transition-colors">
                    98%
                  </p>
                  <p className="text-xs text-muted-foreground uppercase tracking-widest font-semibold mt-1">
                    Satisfação
                  </p>
                </div>
              </motion.div>
            </motion.div>

            {/* RIGHT VISUAL */}
            <motion.div
              style={{ y: heroImageY }}
              className="relative hidden lg:flex items-end justify-end h-full"
            >
              <div className="relative w-full flex items-end h-full">
                {/* Floating Orbs */}
                <div className="absolute inset-0 flex items-center justify-center pointer-events-none">
                  <motion.div
                    style={{ y: orb1Y }}
                    className="absolute w-96 h-96 bg-primary/5 rounded-full blur-3xl animate-pulse"
                  />
                  <motion.div
                    style={{ y: orb2Y }}
                    className="absolute w-72 h-72 bg-secondary/5 rounded-full blur-3xl animate-pulse"
                  />
                </div>

                <div className="relative z-10 w-full max-w-[750px] h-[90%] flex items-end pointer-events-none">
                  <img
                    src="https://nationalhealthcare.co.za/wp-content/uploads/2020/08/healthcare-providers2-2.png"
                    alt="Healthcare Professional"
                    className="w-full h-full object-contain hover:scale-105 transition-transform duration-700 pointer-events-auto object-bottom"
                  />
                </div>
              </div>

              {/* Floating Card */}
              <motion.div
                initial={{ opacity: 0, y: 40, x: -20 }}
                animate={{ opacity: 1, y: 0, x: 0 }}
                transition={{ delay: 0.8, duration: 0.7, ease: [0.22, 1, 0.36, 1] }}
                className="absolute bottom-12 -left-8 z-20 bg-card p-6 shadow-2xl max-w-xs border border-border rounded-2xl backdrop-blur-sm hover:shadow-3xl hover:scale-105 transition-all duration-300 hover:border-primary/30"
              >
                <div className="flex justify-between items-start mb-4">
                  <div className="flex items-center gap-2">
                    <span className="w-2 h-2 bg-primary rounded-full animate-pulse" />
                    <span className="bg-green-100 text-green-800 dark:bg-green-900/30 dark:text-green-400 text-[10px] font-bold px-3 py-1 rounded-full uppercase">
                      Destaque
                    </span>
                  </div>
                  <ArrowUpRight className="text-muted-foreground w-5 h-5" />
                </div>
                <div className="flex items-center gap-4">
                  <div className="w-14 h-14 bg-primary/5 rounded-xl flex items-center justify-center flex-shrink-0 hover:bg-primary/10 transition-colors">
                    <Pill className="text-primary w-6 h-6" />
                  </div>
                  <div>
                    <p className="text-sm font-bold text-foreground leading-tight">
                      Vitamina C + Zinco
                    </p>
                    <p className="text-xs text-muted-foreground mt-1">Premium Imunidade</p>
                    <p className="text-sm font-black text-primary mt-2">Kz 2,000</p>
                  </div>
                </div>
              </motion.div>
            </motion.div>
          </div>
        </motion.div>
      </section>

      {/* PILARES */}
      <section ref={worksRef} className="py-24 px-6 max-w-7xl mx-auto border-t border-border">
        <RevealOnScroll animation="slideUp">
          <div className="mb-16 text-center">
            <span className="inline-block bg-primary/10 text-primary px-4 py-2 rounded-full text-xs font-bold mb-4 uppercase tracking-widest">
              Conheça os Nossos
            </span>
            <h2 className="text-4xl md:text-5xl font-black text-foreground mb-4">
              Pilares do Atendimento
            </h2>
            <div className="w-24 h-2 bg-primary mx-auto rounded-full mt-4" />
          </div>
        </RevealOnScroll>

        <StaggerContainer className="grid md:grid-cols-3 gap-6" staggerDelay={0.15}>
          {/* Card 1 */}
          <StaggerItem animation="slideLeft">
            <div className="group relative bg-card rounded-2xl p-8 border border-border hover:shadow-xl hover:border-primary/20 transition-all duration-300 h-full">
              <div className="absolute inset-0 bg-primary/5 rounded-2xl opacity-0 group-hover:opacity-100 transition-opacity duration-300" />
              <div className="relative z-10">
                <div className="w-14 h-14 bg-primary/5 rounded-2xl flex items-center justify-center mb-6 group-hover:bg-primary/10 transition-colors">
                  <Building2 className="text-primary w-6 h-6" />
                </div>
                <h3 className="text-xl font-bold text-foreground mb-3 font-headline">
                  Rede de Farmácias
                </h3>
                <p className="text-sm text-muted-foreground leading-relaxed mb-6 font-body">
                  Encontre farmácias licenciadas próximas à sua localização com estoque atualizado em tempo real.
                </p>
                <Link href="/farmacias" className="inline-flex items-center gap-2 text-primary font-bold hover:gap-4 transition-all text-sm font-headline">
                  Consultar Stock <ArrowRight className="w-4 h-4" />
                </Link>
              </div>
            </div>
          </StaggerItem>
            
          {/* Card 2 */}
          <StaggerItem animation="slideUp">
            <div className="group relative bg-card rounded-2xl p-8 border border-border hover:shadow-xl hover:border-secondary/20 transition-all duration-300 h-full">
              <div className="absolute inset-0 bg-secondary/5 rounded-2xl opacity-0 group-hover:opacity-100 transition-opacity duration-300" />
              <div className="relative z-10">
                <div className="w-14 h-14 bg-secondary/5 rounded-2xl flex items-center justify-center mb-6 group-hover:bg-secondary/10 transition-colors">
                  <Stethoscope className="text-secondary w-6 h-6" />
                </div>
                <h3 className="text-xl font-bold text-foreground mb-3 font-headline">
                  Hospitais e Centros
                </h3>
                <p className="text-sm text-muted-foreground leading-relaxed mb-6 font-body">
                  Status em tempo real das unidades de saúde públicas e privadas. Verifique tempos de espera e especialidades.
                </p>
                <Link href="/pesquisa" className="inline-flex items-center gap-2 text-secondary font-bold hover:gap-4 transition-all text-sm font-headline">
                  Ver Unidades <ArrowRight className="w-4 h-4" />
                </Link>
              </div>
            </div>
          </StaggerItem>

          {/* Card 3 */}
          <StaggerItem animation="slideRight">
            <div className="group relative bg-card rounded-2xl p-8 border border-border hover:shadow-xl hover:border-primary/20 transition-all duration-300 h-full">
              <div className="absolute inset-0 bg-primary/5 rounded-2xl opacity-0 group-hover:opacity-100 transition-opacity duration-300" />
              <div className="relative z-10">
                <div className="w-14 h-14 bg-primary/5 rounded-2xl flex items-center justify-center mb-6 group-hover:bg-primary/10 transition-colors">
                  <Pill className="text-primary w-6 h-6" />
                </div>
                <h3 className="text-xl font-bold text-foreground mb-3 font-headline">
                  Guia de Sintomas
                </h3>
                <p className="text-sm text-muted-foreground leading-relaxed mb-6 font-body">
                  Orientações oficiais validadas pelo Ministério da Saúde sobre problemas comuns e protocolos de emergência.
                </p>
                <Link href="/suporte" className="inline-flex items-center gap-2 text-primary font-bold hover:gap-4 transition-all text-sm font-headline">
                  Iniciar Triagem <ArrowRight className="w-4 h-4" />
                </Link>
              </div>
            </div>
          </StaggerItem>
        </StaggerContainer>
      </section>

      {/* STATS */}
      <section className="py-20 px-6 bg-muted/20">
        <div className="max-w-7xl mx-auto">
          <StaggerContainer className="grid grid-cols-2 lg:grid-cols-4 gap-8" staggerDelay={0.12}>
            {stats.map((stat) => (
              <StaggerItem key={stat.label} animation="zoomIn">
                <div className="text-center">
                  <div className="flex justify-center mb-4">
                    <div className="w-16 h-16 bg-primary/10 rounded-2xl flex items-center justify-center">
                      <stat.icon className="w-8 h-8 text-primary" />
                    </div>
                  </div>
                  <p className="text-4xl md:text-5xl font-black text-foreground mb-2">
                    {stat.value}
                  </p>
                  <p className="text-sm text-muted-foreground uppercase tracking-widest font-bold">
                    {stat.label}
                  </p>
                </div>
              </StaggerItem>
            ))}
          </StaggerContainer>
        </div>
      </section>

      {/* HOW IT WORKS */}
      <section id="como-funciona" className="py-24 px-6 relative bg-background border-t border-border z-10">
        <div className="max-w-6xl mx-auto">
          <RevealOnScroll animation="slideUp">
            <div className="text-center mb-16">
              <span className="inline-block bg-primary/10 text-primary px-4 py-2 rounded-full text-xs font-bold mb-4 uppercase tracking-widest">
                Processo
              </span>
              <h2 className="text-4xl md:text-5xl font-black text-foreground mb-4">
                Como <span className="text-primary">funciona</span> a plataforma
              </h2>
              <p className="text-muted-foreground max-w-2xl mx-auto text-lg font-light">
                Um processo simples e intuitivo em apenas três passos.
              </p>
            </div>
          </RevealOnScroll>

          <div className="grid grid-cols-1 md:grid-cols-3 gap-8 relative">
            <div className="hidden md:block absolute top-20 left-0 w-full h-1 bg-gradient-to-r from-primary/20 via-primary/10 to-primary/20" />

            <StaggerContainer className="grid grid-cols-1 md:grid-cols-3 gap-8 col-span-full" staggerDelay={0.18}>
              {steps.map((s, idx) => (
                <StaggerItem key={s.number} animation="slideRight">
                  <div className="relative h-full">
                    <div className="bg-card rounded-2xl p-8 border border-border hover:shadow-xl hover:border-primary/30 transition-all relative z-10 h-full">
                      <div className="flex items-center gap-4 mb-6">
                        <div className="w-16 h-16 bg-primary/10 rounded-2xl flex items-center justify-center flex-shrink-0">
                          <s.icon className="text-primary w-6 h-6" />
                        </div>
                        <div className="text-4xl font-black text-primary/20">{s.number}</div>
                      </div>
                      <h3 className="text-2xl font-bold text-foreground mb-3 font-headline">
                        {s.title}
                      </h3>
                      <p className="text-muted-foreground leading-relaxed font-body">
                        {s.desc}
                      </p>
                    </div>
                    {idx < steps.length - 1 && (
                      <div className="hidden md:block absolute -right-4 top-12 z-20">
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

      {/* CTA */}
      <section className="py-24 px-6 relative overflow-hidden bg-primary/5">
        <RevealOnScroll animation="zoomIn">
          <div className="max-w-4xl mx-auto relative z-10 text-center">
            <span className="inline-block bg-primary/10 text-primary px-4 py-2 rounded-full text-xs font-bold mb-6 uppercase tracking-widest">
              Pronto para começar
            </span>
            <h2 className="text-4xl md:text-5xl font-black text-foreground font-headline mb-6">
              Encontre medicamentos com{" "}
              <span className="text-primary">confiança</span>
            </h2>
            <p className="text-lg text-muted-foreground max-w-2xl mx-auto mb-10 font-light leading-relaxed">
              Junte-se a milhares de angolanos que já confiam na nossa rede de
              saúde integrada. Encontre clínicas, hospitais e farmácias com
              facilidade.
            </p>
            <Link
              href="/pesquisa"
              className="inline-flex items-center gap-3 bg-primary text-primary-foreground px-10 py-4 rounded-xl text-base font-bold hover:opacity-90 transition-all hover:shadow-lg hover:scale-105"
            >
              <Search className="w-5 h-5" />
              Começar Pesquisa Agora
            </Link>
          </div>
        </RevealOnScroll>
      </section>

      {/* TRUST */}
      <section className="py-20 px-6 bg-slate-900 border-t border-slate-800">
        <div className="max-w-7xl mx-auto">
          <StaggerContainer className="grid grid-cols-1 md:grid-cols-3 gap-8" staggerDelay={0.14}>
            <StaggerItem animation="slideUp">
              <div className="text-center p-8 bg-white/5 rounded-2xl border border-white/10 h-full">
                <ShieldCheck className="text-primary w-12 h-12 mx-auto mb-4" />
                <h3 className="text-lg font-bold text-white mb-2">100% Seguro</h3>
                <p className="text-sm text-white/70">
                  Dados criptografados e transações protegidas.
                </p>
              </div>
            </StaggerItem>
            <StaggerItem animation="slideUp">
              <div className="text-center p-8 bg-white/5 rounded-2xl border border-white/10 h-full">
                <CheckCircle2 className="text-primary w-12 h-12 mx-auto mb-4" />
                <h3 className="text-lg font-bold text-white mb-2">Farmácias Verificadas</h3>
                <p className="text-sm text-white/70">
                  Apenas parceiros certificados e confiáveis.
                </p>
              </div>
            </StaggerItem>
            <StaggerItem animation="slideUp">
              <div className="text-center p-8 bg-white/5 rounded-2xl border border-white/10 h-full">
                <Clock className="text-primary w-12 h-12 mx-auto mb-4" />
                <h3 className="text-lg font-bold text-white mb-2">Entrega Rápida</h3>
                <p className="text-sm text-white/70">
                  Levante ou entrega em até 24 horas.
                </p>
              </div>
            </StaggerItem>
          </StaggerContainer>
        </div>
      </section>

      {/* FOOTER */}
      <RevealOnScroll animation="fadeIn" duration={0.8}>
        <footer className="bg-slate-900 text-white py-16 px-6">
          <div className="max-w-7xl mx-auto">
            <div className="grid grid-cols-1 md:grid-cols-4 gap-12 mb-12">
              <div>
                <h3 className="text-2xl font-black mb-4 flex items-center gap-2">
                  <Pill className="text-primary w-6 h-6" />
                  Apothecary <span className="text-primary">Angola</span>
                </h3>
                <p className="text-white/70 text-sm mb-6">
                  A plataforma mais confiável para encontrar medicamentos em Angola.
                </p>
                <div className="flex gap-4">
                  <a href="#" className="w-10 h-10 bg-white/10 rounded-lg flex items-center justify-center hover:bg-primary transition-colors">
                    <Mail className="w-5 h-5" />
                  </a>
                </div>
              </div>

              <div>
                <h4 className="font-bold text-white mb-4 uppercase text-xs tracking-widest">Produto</h4>
                <ul className="space-y-3 text-sm">
                  <li><Link href="/pesquisa" className="text-white/70 hover:text-primary transition-colors">Pesquisar</Link></li>
                  <li><Link href="/farmacias" className="text-white/70 hover:text-primary transition-colors">Farmácias</Link></li>
                </ul>
              </div>
              <div>
                <h4 className="font-bold text-white mb-4 uppercase text-xs tracking-widest">Empresa</h4>
                <ul className="space-y-3 text-sm">
                  <li><a href="#" className="text-white/70 hover:text-primary transition-colors">Sobre Nós</a></li>
                  <li><Link href="/suporte" className="text-white/70 hover:text-primary transition-colors">Contacto</Link></li>
                </ul>
              </div>
              <div>
                <h4 className="font-bold text-white mb-4 uppercase text-xs tracking-widest">Legal</h4>
                <ul className="space-y-3 text-sm">
                  <li><a href="#" className="text-white/70 hover:text-primary transition-colors">Privacidade</a></li>
                  <li><a href="#" className="text-white/70 hover:text-primary transition-colors">Termos de Uso</a></li>
                </ul>
              </div>
            </div>

            <div className="border-t border-white/10 pt-8">
              <div className="flex flex-col md:flex-row items-center justify-between gap-4">
                <p className="text-sm text-white/50">
                  © 2026 Apothecary Angola. Todos os direitos reservados.
                </p>
                <p className="text-sm text-white/50">
                  Desenvolvido com ❤️ para Angola
                </p>
              </div>
            </div>
          </div>
        </footer>
      </RevealOnScroll>
    </div>
  )
}

function ScrollViewIcon() {
  return (
    <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
      <path d="M7 21h10a2 2 0 0 0 2-2V5a2 2 0 0 0-2-2H7a2 2 0 0 0-2 2v14a2 2 0 0 0 2 2z"/>
      <path d="m9 9 2 2 4-4"/>
      <path d="M9 13h6"/>
      <path d="M9 17h6"/>
    </svg>
  )
}
