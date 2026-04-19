"use client"

import { useState } from "react"
import { User, MapPin, Phone, Mail, Shield, Bell, LogOut, ChevronRight, Edit2, Check, X, Camera } from "lucide-react"
import { Button } from "@/components/ui/button"
import { Input } from "@/components/ui/input"
import { Switch } from "@/components/ui/switch"
import Image from "next/image"

export default function PerfilPage() {
  const [isEditing, setIsEditing] = useState(false)
  const [profile, setProfile] = useState({
    name: "João Silva",
    location: "Luanda, Angola",
    phone: "+244 923 456 789",
    email: "joao.silva@email.com",
  })
  
  const [settings, setSettings] = useState({
    locationShared: true,
    notifications: true,
    privacy: false
  })

  // Estado temporário para não alterar os dados até que clique em Gravar
  const [tempProfile, setTempProfile] = useState(profile)

  const handleSave = () => {
    setProfile(tempProfile)
    setIsEditing(false)
  }

  const handleCancel = () => {
    setTempProfile(profile)
    setIsEditing(false)
  }

  return (
    <div className="px-6 md:px-12 max-w-3xl mx-auto py-8 space-y-8">
      {/* Profile Header & Contact Info (Editable Area) */}
      <div className="bg-card rounded-3xl p-8 shadow-sm relative">
        {/* Toggle Edit Button */}
        {!isEditing ? (
          <Button 
            variant="ghost" 
            className="absolute top-6 right-6 w-10 h-10 p-0 rounded-full hover:bg-primary/10 hover:text-primary transition-colors"
            onClick={() => setIsEditing(true)}
          >
            <Edit2 className="w-5 h-5" />
          </Button>
        ) : (
          <div className="absolute top-6 right-6 flex items-center gap-2">
            <Button 
              variant="ghost" 
              className="w-10 h-10 p-0 rounded-full text-destructive hover:bg-destructive/10"
              onClick={handleCancel}
            >
              <X className="w-5 h-5" />
            </Button>
            <Button 
              variant="default" 
              className="w-10 h-10 p-0 rounded-full bg-green-600 hover:bg-green-700 text-white"
              onClick={handleSave}
            >
              <Check className="w-5 h-5" />
            </Button>
          </div>
        )}

        <div className="flex flex-col md:flex-row items-start md:items-center gap-8">
          {/* Avatar Area */}
          <div className="relative group mx-auto md:mx-0">
            <div className="w-28 h-28 rounded-full overflow-hidden border-4 border-primary/20 bg-muted">
              <Image
                src="https://images.unsplash.com/photo-1472099645785-5658abf4ff4e?w=200&h=200&fit=crop&crop=face"
                alt="Foto de perfil"
                width={112}
                height={112}
                className="w-full h-full object-cover"
              />
            </div>
            {isEditing && (
              <button className="absolute bottom-0 right-0 w-8 h-8 rounded-full bg-primary text-primary-foreground flex items-center justify-center shadow-lg hover:scale-105 transition-transform border-2 border-white">
                <Camera className="w-4 h-4" />
              </button>
            )}
          </div>

          {/* Profile Basic Info */}
          <div className="flex-1 w-full text-center md:text-left">
            {isEditing ? (
              <div className="space-y-3 max-w-sm mx-auto md:mx-0">
                <div>
                  <p className="text-xs text-muted-foreground font-medium mb-1">Nome Completo</p>
                  <Input 
                    value={tempProfile.name} 
                    onChange={e => setTempProfile({...tempProfile, name: e.target.value})}
                    className="font-bold font-serif text-lg h-10"
                  />
                </div>
                <div>
                  <p className="text-xs text-muted-foreground font-medium mb-1">Localização</p>
                  <div className="relative">
                    <MapPin className="w-4 h-4 absolute left-3 top-1/2 -translate-y-1/2 text-muted-foreground" />
                    <Input 
                      value={tempProfile.location} 
                      onChange={e => setTempProfile({...tempProfile, location: e.target.value})}
                      className="pl-9 h-10"
                    />
                  </div>
                </div>
              </div>
            ) : (
              <>
                <h1 className="text-3xl font-extrabold text-foreground font-serif">{profile.name}</h1>
                <p className="text-muted-foreground flex items-center justify-center md:justify-start gap-2 mt-1">
                  <MapPin className="w-4 h-4" />
                  {profile.location}
                </p>
                <div className="flex gap-6 mt-6 justify-center md:justify-start">
                  <div className="text-center">
                    <p className="text-2xl font-bold text-primary">5</p>
                    <p className="text-[10px] text-muted-foreground font-bold uppercase tracking-widest mt-1">Favoritos</p>
                  </div>
                  <div className="text-center">
                    <p className="text-2xl font-bold text-primary">8</p>
                    <p className="text-[10px] text-muted-foreground font-bold uppercase tracking-widest mt-1">Receitas</p>
                  </div>
                  <div className="text-center">
                    <p className="text-2xl font-bold text-tertiary">Gold</p>
                    <p className="text-[10px] text-muted-foreground font-bold uppercase tracking-widest mt-1">Nível</p>
                  </div>
                </div>
              </>
            )}
          </div>
        </div>

        {/* Contact Info Block */}
        <div className="mt-8 pt-8 border-t border-border/10 grid grid-cols-1 md:grid-cols-2 gap-6">
          <div className="flex items-center gap-4">
            <div className="w-12 h-12 rounded-2xl bg-primary/5 flex items-center justify-center text-primary flex-shrink-0">
              <Phone className="w-5 h-5" />
            </div>
            <div className="flex-1">
              <p className="text-xs text-muted-foreground font-medium mb-1.5">Telefone</p>
              {isEditing ? (
                <Input 
                  value={tempProfile.phone} 
                  onChange={e => setTempProfile({...tempProfile, phone: e.target.value})}
                  className="h-9"
                />
              ) : (
                <p className="text-sm font-semibold text-foreground">{profile.phone}</p>
              )}
            </div>
          </div>
          <div className="flex items-center gap-4">
            <div className="w-12 h-12 rounded-2xl bg-primary/5 flex items-center justify-center text-primary flex-shrink-0">
              <Mail className="w-5 h-5" />
            </div>
            <div className="flex-1 overflow-hidden">
              <p className="text-xs text-muted-foreground font-medium mb-1.5">Email</p>
              {isEditing ? (
                <Input 
                  value={tempProfile.email} 
                  onChange={e => setTempProfile({...tempProfile, email: e.target.value})}
                  type="email"
                  className="h-9"
                />
              ) : (
                <p className="text-sm font-semibold text-foreground truncate">{profile.email}</p>
              )}
            </div>
          </div>
        </div>
      </div>

      {/* Settings Options */}
      <div className="bg-card rounded-3xl shadow-sm overflow-hidden">
        {/* Location Sharing */}
        <label className="flex items-center justify-between p-6 border-b border-border/10 hover:bg-muted/50 transition-colors cursor-pointer">
          <div className="flex items-center gap-4">
            <div className="w-12 h-12 rounded-2xl bg-muted flex items-center justify-center text-primary">
              <MapPin className="w-5 h-5" />
            </div>
            <div>
              <p className="text-sm font-bold text-foreground">Partilhar Localização</p>
              <p className="text-xs text-muted-foreground">Permitir acesso à sua localização atual</p>
            </div>
          </div>
          <Switch 
            checked={settings.locationShared}
            onCheckedChange={(checked) => setSettings({...settings, locationShared: checked})}
          />
        </label>

        {/* Notifications */}
        <label className="flex items-center justify-between p-6 border-b border-border/10 hover:bg-muted/50 transition-colors cursor-pointer">
          <div className="flex items-center gap-4">
            <div className="w-12 h-12 rounded-2xl bg-muted flex items-center justify-center text-primary">
              <Bell className="w-5 h-5" />
            </div>
            <div>
              <p className="text-sm font-bold text-foreground">Notificações</p>
              <p className="text-xs text-muted-foreground">Alertas de medicamentos e lembretes</p>
            </div>
          </div>
          <Switch 
            checked={settings.notifications}
            onCheckedChange={(checked) => setSettings({...settings, notifications: checked})}
          />
        </label>

        {/* Privacy */}
        <label className="flex items-center justify-between p-6 hover:bg-muted/50 transition-colors cursor-pointer">
          <div className="flex items-center gap-4">
            <div className="w-12 h-12 rounded-2xl bg-muted flex items-center justify-center text-primary">
              <Shield className="w-5 h-5" />
            </div>
            <div>
              <p className="text-sm font-bold text-foreground">Conta Privada</p>
              <p className="text-xs text-muted-foreground">Ocultar o seu histórico de consultas</p>
            </div>
          </div>
          <Switch 
            checked={settings.privacy}
            onCheckedChange={(checked) => setSettings({...settings, privacy: checked})}
          />
        </label>
      </div>

      {/* Logout Button */}
      <Button variant="outline" className="w-full rounded-2xl py-6 text-destructive border-destructive/30 hover:bg-destructive/10 hover:border-destructive font-bold text-base shadow-sm">
        <LogOut className="w-5 h-5 mr-3" />
        Terminar Sessão
      </Button>
    </div>
  )
}
