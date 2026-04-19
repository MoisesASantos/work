"use client"

import { User, MapPin, Phone, Mail, Shield, Bell, LogOut, ChevronRight } from "lucide-react"
import { Button } from "@/components/ui/button"
import Image from "next/image"

const menuItems = [
  { icon: User, label: "Dados Pessoais", description: "Nome, email e telefone" },
  { icon: MapPin, label: "Localizacao", description: "Gerir a sua localizacao" },
  { icon: Bell, label: "Notificacoes", description: "Alertas e lembretes" },
  { icon: Shield, label: "Privacidade", description: "Dados e permissoes" },
]

export default function PerfilPage() {
  return (
    <div className="px-6 md:px-12 max-w-3xl mx-auto py-8">
      {/* Profile Header */}
      <div className="bg-card rounded-3xl p-8 shadow-sm mb-8">
        <div className="flex flex-col md:flex-row items-center gap-6">
          <div className="w-24 h-24 rounded-full overflow-hidden border-4 border-primary/20">
            <Image
              src="https://images.unsplash.com/photo-1472099645785-5658abf4ff4e?w=200&h=200&fit=crop&crop=face"
              alt="Foto de perfil"
              width={96}
              height={96}
              className="w-full h-full object-cover"
            />
          </div>
          <div className="text-center md:text-left">
            <h1 className="text-2xl font-extrabold text-foreground font-serif">Joao Silva</h1>
            <p className="text-muted-foreground flex items-center justify-center md:justify-start gap-2 mt-1">
              <MapPin className="w-4 h-4" />
              Luanda, Angola
            </p>
            <div className="flex gap-4 mt-4">
              <div className="text-center">
                <p className="text-2xl font-bold text-primary">5</p>
                <p className="text-xs text-muted-foreground">Favoritos</p>
              </div>
              <div className="text-center">
                <p className="text-2xl font-bold text-primary">8</p>
                <p className="text-xs text-muted-foreground">Receitas</p>
              </div>
              <div className="text-center">
                <p className="text-2xl font-bold text-tertiary">Gold</p>
                <p className="text-xs text-muted-foreground">Nivel</p>
              </div>
            </div>
          </div>
        </div>
      </div>

      {/* Contact Info */}
      <div className="bg-card rounded-2xl p-6 shadow-sm mb-8">
        <h2 className="text-lg font-bold text-foreground mb-4">Informacoes de Contacto</h2>
        <div className="space-y-4">
          <div className="flex items-center gap-4">
            <div className="w-10 h-10 rounded-xl bg-muted flex items-center justify-center text-primary">
              <Phone className="w-5 h-5" />
            </div>
            <div>
              <p className="text-xs text-muted-foreground">Telefone</p>
              <p className="text-sm font-medium text-foreground">+244 923 456 789</p>
            </div>
          </div>
          <div className="flex items-center gap-4">
            <div className="w-10 h-10 rounded-xl bg-muted flex items-center justify-center text-primary">
              <Mail className="w-5 h-5" />
            </div>
            <div>
              <p className="text-xs text-muted-foreground">Email</p>
              <p className="text-sm font-medium text-foreground">joao.silva@email.com</p>
            </div>
          </div>
        </div>
      </div>

      {/* Menu Items */}
      <div className="bg-card rounded-2xl shadow-sm overflow-hidden mb-8">
        {menuItems.map((item, index) => (
          <button
            key={item.label}
            className={`w-full flex items-center gap-4 p-4 hover:bg-muted transition-colors text-left ${
              index !== menuItems.length - 1 ? "border-b border-border/10" : ""
            }`}
          >
            <div className="w-10 h-10 rounded-xl bg-muted flex items-center justify-center text-primary">
              <item.icon className="w-5 h-5" />
            </div>
            <div className="flex-1">
              <p className="text-sm font-medium text-foreground">{item.label}</p>
              <p className="text-xs text-muted-foreground">{item.description}</p>
            </div>
            <ChevronRight className="w-5 h-5 text-muted-foreground" />
          </button>
        ))}
      </div>

      {/* Logout Button */}
      <Button variant="outline" className="w-full rounded-2xl py-6 text-destructive border-destructive/30 hover:bg-destructive/10">
        <LogOut className="w-5 h-5 mr-2" />
        Terminar Sessao
      </Button>
    </div>
  )
}
